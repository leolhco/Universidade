/**
 * @file transform.c
 * @brief Implementação das transformações geométricas 2D em coordenadas homogêneas.
 *
 * Implementa manualmente a álgebra linear usada pelo jogo para mover,
 * girar e escalar os vértices dos objetos: construção das matrizes
 * elementares (translação, escala, rotação), composição por multiplicação
 * de matrizes e aplicação da matriz resultante a cada ponto. Nenhuma
 * biblioteca de matemática gráfica (GLM ou similar) é utilizada.
 *
 * **Convenção vetor-linha:** os pontos são tratados como vetores-linha
 * homogêneos [x, y, 1] multiplicados À ESQUERDA da matriz (p' = p · M).
 * Por isso:
 * - a translação ocupa a TERCEIRA LINHA da matriz (e não a terceira coluna);
 * - a composição lê-se da esquerda para a direita: mul(A, B) aplica A
 *   primeiro e B depois.
 */

#include "transform.h"
#include <math.h>

/**
 * @brief Constrói a matriz homogênea de translação por (dx, dy).
 *
 * **Por que a translação precisa da coordenada homogênea:** a translação
 * não é linear (T(p + q) != T(p) + T(q)), logo não cabe em uma matriz 2x2.
 * Com o ponto estendido para [x, y, 1], a terceira componente fixa em 1
 * "carrega" os deslocamentos durante o produto:
 *
 *     [x y 1] · M = [x·1 + y·0 + 1·dx,  x·0 + y·1 + 1·dy,  1]
 *                 = [x + dx, y + dy, 1]
 *
 * A submatriz superior é a identidade (a parte linear não altera nada) e
 * dx, dy ficam na terceira LINHA — consequência direta da convenção
 * vetor-linha adotada no projeto.
 *
 * @param dx Deslocamento horizontal.
 * @param dy Deslocamento vertical.
 * @return Matriz de translação 3x3.
 */
Mat3 translation(float dx, float dy)
{
	Mat3 res = {
		.m = {
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ dx, dy, 1.0f }
		}
	};

	return res;
}

/**
 * @brief Constrói a matriz de escala por fatores (sx, sy).
 *
 * Escala é uma transformação linear pura: basta colocar os fatores na
 * diagonal da submatriz 2x2 ([x y 1] · M = [sx·x, sy·y, 1]). Fatores
 * distintos em x e y produzem escala não uniforme (esticamento);
 * fatores negativos produzem espelhamento em torno do eixo correspondente.
 *
 * @param sx Fator de escala horizontal.
 * @param sy Fator de escala vertical.
 * @return Matriz de escala 3x3.
 *
 * @warning A escala é relativa à ORIGEM do sistema de coordenadas: pontos
 *          longe da origem também se afastam/aproximam dela. Para escalar
 *          um objeto "no lugar", componha com translações de ida e volta
 *          ao seu centro.
 */
Mat3 scale(float sx, float sy)
{
	Mat3 res = { 
		.m = {
			{ sx, 0.0f, 0.0f },
			{ 0.0f, sy, 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		}
	};

	return res;
}

/**
 * @brief Constrói a matriz de rotação pelo ângulo @p theta (em radianos).
 *
 * **Derivação:** uma rotação fica completamente determinada pelo destino
 * dos vetores da base canônica: e1 = (1, 0) vai para (cosθ, sinθ) e
 * e2 = (0, 1) vai para (-sinθ, cosθ). Na convenção vetor-linha, essas
 * imagens formam as LINHAS da submatriz 2x2, de modo que:
 *
 *     [x y 1] · M = [x·cosθ + y·sinθ,  -x·sinθ + y·cosθ,  1]
 *
 * que é a fórmula clássica de rotação de um ponto em torno da origem.
 *
 * @param theta Ângulo de rotação, em RADIANOS (use graus * M_PI / 180 para converter).
 * @return Matriz de rotação 3x3.
 *
 * @note Em coordenadas de tela (eixo y crescendo para BAIXO), um θ
 *       positivo aparece visualmente como rotação horária — espelho da
 *       convenção matemática usual, causado pela inversão do eixo y.
 * @warning A rotação é em torno da ORIGEM. Para girar um sprite/forma em
 *          torno do próprio centro c — o caso típico no jogo — usa-se a
 *          composição translação(-cx, -cy) · rotação(θ) · translação(cx, cy):
 *          leva-se o centro do objeto à origem, gira-se e devolve-se ao lugar.
 */
Mat3 rotation(float theta)
{
	float c = cosf(theta);
	float s = sinf(theta);

	Mat3 res = {
		.m = {
			{ c, -s, 0.0f },
			{ s, c, 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		}
	};

	return res;
}

/**
 * @brief Multiplica (compõe) duas matrizes 3x3: res = a · b.
 *
 * Implementação direta da definição: res[i][j] é o produto escalar da
 * linha i de @p a pela coluna j de @p b (o laço em k acumula a soma dos
 * produtos termo a termo). É a operação que torna o sistema de matrizes
 * poderoso: uma cadeia inteira de transformações — por exemplo, o pipeline
 * "centralizar → rotacionar → escalar → posicionar no mundo" de um objeto
 * do jogo — colapsa em UMA única matriz, e cada vértice paga apenas uma
 * multiplicação ponto-matriz, independentemente de quantas transformações
 * foram compostas.
 *
 * @param a Primeira matriz (na convenção vetor-linha, transformação aplicada PRIMEIRO).
 * @param b Segunda matriz (transformação aplicada DEPOIS).
 * @return A matriz produto a · b.
 *
 * @note Complexidade O(3³) = 27 multiplicações — custo fixo e desprezível,
 *       pago uma vez por objeto por frame, e não por vértice.
 * @warning A multiplicação NÃO comuta: mul(translation(...), rotation(...))
 *          difere de mul(rotation(...), translation(...)) — a ordem das
 *          transformações altera o resultado geométrico.
 */
Mat3 mul(Mat3 a, Mat3 b)
{
	Mat3 res;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += a.m[i][k] * b.m[k][j];
			}
			res.m[i][j] = sum;
		}
	}

	return res;
}

/**
 * @brief Aplica a transformação @p M ao ponto (*x, *y), in-place.
 *
 * Realiza o produto vetor-linha homogêneo [x, y, 1] · M, com a terceira
 * componente implícita em 1 — repare que m[2][0] e m[2][1] (a translação)
 * são somados sem multiplicação, pois multiplicariam exatamente por 1:
 *
 *     x' = x·m[0][0] + y·m[1][0] + 1·m[2][0]
 *     y' = x·m[0][1] + y·m[1][1] + 1·m[2][1]
 *
 * A terceira componente do resultado não é calculada porque, para
 * transformações afins (sem projeção), ela permanece sempre 1.
 *
 * @param x Ponteiro para a coordenada x (lida e sobrescrita com o resultado).
 * @param y Ponteiro para a coordenada y (lida e sobrescrita com o resultado).
 * @param M Matriz de transformação composta a aplicar.
 * @return Nenhum (saída via @p x e @p y).
 *
 * @note As cópias intermediárias xp/yp são essenciais: como a saída
 *       sobrescreve a entrada, calcular y' usando um x já transformado
 *       corromperia o resultado.
 * @note No jogo, esta função é chamada para cada vértice de cada objeto a
 *       cada frame, na etapa de atualização geométrica, ANTES da
 *       rasterização — mantendo a separação entre lógica (transformar) e
 *       renderização (desenhar).
 */
void transform(float *x, float *y, Mat3 M)
{
	float (*m)[3] = M.m;

	float xp = *x;
	float yp = *y;

	float xc = xp * m[0][0] + yp * m[1][0] + m[2][0];
	float yc = xp * m[0][1] + yp * m[1][1] + m[2][1];

	*x = xc;
	*y = yc;
}
