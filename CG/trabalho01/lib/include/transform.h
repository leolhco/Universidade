/**
 * @file transform.h
 * @brief Interface das transformações geométricas 2D em coordenadas homogêneas.
 *
 * Define a matriz 3x3 e as fábricas das três transformações afins
 * fundamentais — translação, escala e rotação — além da multiplicação de
 * matrizes (composição) e da aplicação de uma transformação a um ponto.
 *
 * **Por que matrizes 3x3 para um mundo 2D?** A translação NÃO é uma
 * transformação linear em 2D (não pode ser expressa como multiplicação por
 * matriz 2x2, pois move a origem). Adicionando uma terceira coordenada
 * homogênea fixa em 1 — pontos representados como [x, y, 1] — a translação
 * passa a ser uma multiplicação de matriz como qualquer outra. Isso
 * permite COMPOR transformações arbitrárias (ex.: girar um sprite em torno
 * do próprio centro = transladar para a origem, rotacionar, transladar de
 * volta) em uma ÚNICA matriz via mul(), aplicada depois a todos os
 * vértices de uma só vez.
 *
 * @note Convenção adotada: VETOR-LINHA. Os pontos são multiplicados à
 *       esquerda da matriz (p' = p · M), e por isso os termos de translação
 *       ocupam a TERCEIRA LINHA da matriz (m[2][0] = dx, m[2][1] = dy) —
 *       transposta da convenção vetor-coluna comum em livros-texto.
 * @warning Consequência da convenção vetor-linha: a composição lê-se da
 *          ESQUERDA para a direita. mul(A, B) aplica A primeiro e B depois.
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

/**
 * @brief Matriz 3x3 de transformação afim 2D em coordenadas homogêneas.
 *
 * Armazena qualquer combinação de translação, rotação e escala (e suas
 * composições). A submatriz 2x2 superior esquerda codifica a parte linear
 * (rotação/escala) e a terceira linha carrega a translação.
 */
struct mat3 {
	float m[3][3]; /**< Elementos da matriz, indexados como m[linha][coluna]. */
};
typedef struct mat3 Mat3; /**< Apelido de tipo para @ref mat3. */

/**
 * @brief Constrói a matriz de translação por (dx, dy).
 * @param dx Deslocamento horizontal.
 * @param dy Deslocamento vertical.
 * @return Matriz 3x3 que, aplicada a um ponto, soma (dx, dy) às suas coordenadas.
 * @note Os deslocamentos residem na terceira linha (convenção vetor-linha):
 *       [x y 1] · M = [x + dx, y + dy, 1].
 */
Mat3 translation(float dx, float dy);

/**
 * @brief Constrói a matriz de escala por fatores (sx, sy).
 * @param sx Fator de escala horizontal.
 * @param sy Fator de escala vertical.
 * @return Matriz 3x3 diagonal que multiplica x por sx e y por sy.
 * @warning A escala é sempre relativa à ORIGEM. Para escalar em torno de
 *          um ponto arbitrário, componha: translação(-p) · escala · translação(p).
 */
Mat3 scale(float sx, float sy);

/**
 * @brief Constrói a matriz de rotação pelo ângulo @p theta.
 * @param theta Ângulo de rotação, em RADIANOS.
 * @return Matriz 3x3 de rotação em torno da origem.
 * @note Deriva da rotação do par de vetores da base canônica:
 *       (1,0) → (cosθ, sinθ) e (0,1) → (-sinθ, cosθ).
 * @warning A rotação é sempre em torno da ORIGEM. Para girar um objeto em
 *          torno do próprio centro c, componha:
 *          translação(-c) · rotação(θ) · translação(c).
 *          Em tela com eixo y para baixo, θ > 0 aparece como giro horário.
 */
Mat3 rotation(float theta);

/**
 * @brief Multiplica (compõe) duas matrizes: res = a · b.
 * @param a Primeira matriz (transformação aplicada PRIMEIRO, na convenção vetor-linha).
 * @param b Segunda matriz (transformação aplicada DEPOIS).
 * @return A matriz produto, que aplica as duas transformações de uma só vez.
 * @note É a peça-chave da eficiência: N transformações compostas custam
 *       uma única multiplicação matriz-vetor por vértice, em vez de N.
 * @warning Multiplicação de matrizes NÃO é comutativa: mul(a, b) != mul(b, a)
 *          em geral (girar e depois transladar ≠ transladar e depois girar).
 */
Mat3 mul(Mat3 a, Mat3 b);

/**
 * @brief Aplica a transformação @p M ao ponto (*x, *y), modificando-o no lugar.
 * @param x Ponteiro para a coordenada x do ponto (entrada e saída).
 * @param y Ponteiro para a coordenada y do ponto (entrada e saída).
 * @param M Matriz de transformação a aplicar.
 * @return Nenhum (resultado devolvido via @p x e @p y).
 * @note Calcula [x y 1] · M, com a coordenada homogênea implícita em 1;
 *       é a rotina chamada para cada vértice dos objetos do jogo antes da
 *       rasterização.
 */
void transform(float *x, float *y, Mat3 M);

#endif
