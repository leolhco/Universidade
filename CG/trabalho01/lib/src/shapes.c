/**
 * @file shapes.c
 * @brief Implementação manual dos algoritmos clássicos de rasterização e dos testes de colisão.
 *
 * Núcleo matemático do projeto. Aqui estão implementados "do zero", sem
 * qualquer função de desenho de biblioteca de alto nível:
 *
 * - **Algoritmo de Bresenham** (generalizado para todos os octantes) para
 *   segmentos de reta, usando exclusivamente aritmética inteira;
 * - **Algoritmo do ponto médio** (variante de Bresenham para círculos),
 *   explorando a simetria de 8 octantes da circunferência;
 * - **Preenchimento de triângulos por varredura (scanline)**, com ordenação
 *   de vértices e interpolação incremental das bordas;
 * - **Decomposição geométrica**: retângulos, polígonos e linhas espessas
 *   reduzidos a triângulos/linhas;
 * - **Testes analíticos de colisão** (ponto/retângulo, ponto/círculo,
 *   círculo/retângulo, círculo/círculo) usados pela lógica do jogo,
 *   completamente desacoplados da renderização.
 *
 * @note Todas as primitivas escrevem pixels apenas através de
 *       canvas_put_pixel() (via draw_point() / draw_line()), garantindo
 *       clipping uniforme e um único caminho de acesso ao framebuffer.
 */

#include "shapes.h"
#include <math.h>

/**
 * @brief Valor absoluto de @p x.
 * @param x Expressão numérica.
 * @return (Valor da expressão) |x|.
 * @warning Como toda macro, avalia @p x mais de uma vez; não usar com
 *          expressões com efeitos colaterais (ex.: ABS(i++)).
 */
#define ABS(x) (((x) < 0) ? -(x) : (x))

/**
 * @brief Função sinal de @p x.
 * @param x Expressão numérica.
 * @return (Valor da expressão) +1 se x > 0, -1 se x < 0, 0 se x == 0.
 * @note Implementada como diferença de comparações booleanas — truque sem
 *       ramificação usado para definir a direção de passo (incremento ou
 *       decremento) no algoritmo de Bresenham.
 */
#define SIGN(x) (((x) > 0) - ((x) < 0))

/**
 * @brief Máximo entre @p a e @p b.
 * @param a Primeiro valor.
 * @param b Segundo valor.
 * @return (Valor da expressão) O maior dos dois.
 * @warning Avalia os argumentos duas vezes (macro).
 */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/**
 * @brief Mínimo entre @p a e @p b.
 * @param a Primeiro valor.
 * @param b Segundo valor.
 * @return (Valor da expressão) O menor dos dois.
 * @warning Avalia os argumentos duas vezes (macro).
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/**
 * @brief Rasteriza um único ponto: converte o Vec2 (float) para a grade
 *        inteira de pixels e delega a escrita ao framebuffer.
 *
 * @param canvas Canvas alvo.
 * @param point  Coordenadas do ponto.
 * @param color  Cor RGBA de 32 bits.
 * @return Nenhum.
 *
 * @note A conversão float→int ocorre por truncamento na passagem de
 *       parâmetros para canvas_put_pixel(). O clipping de tela é herdado
 *       da própria primitiva de escrita.
 */
void draw_point(Canvas *canvas, Vec2 *point, uint32_t color)
{
	canvas_put_pixel(canvas, point->x, point->y, color);
}

/**
 * @brief Traça um segmento de reta pelo algoritmo de Bresenham generalizado.
 *
 * **Por que Bresenham?** A equação contínua da reta exigiria multiplicações
 * e aritmética em ponto flutuante por pixel. Bresenham substitui isso por
 * um *termo de erro inteiro acumulado*: a cada passo no eixo dominante
 * (major), o erro cresce 2*minor_delta; quando ultrapassa zero, significa
 * que a reta ideal já cruzou o ponto médio entre dois pixels vizinhos, e
 * então o eixo secundário (minor) avança um pixel e o erro é corrigido em
 * -2*major_delta. O fator 2 elimina frações (o teste original compararia
 * com 0.5), mantendo TODA a aritmética em inteiros — exatamente o espírito
 * da rasterização clássica exigida no trabalho.
 *
 * **Generalização por ponteiros:** em vez de escrever 8 variantes (uma por
 * octante), a implementação escolhe dinamicamente qual coordenada é o eixo
 * dominante (aquele com maior |delta|) e aponta @c major_coord /
 * @c minor_coord para @c x ou @c y. A direção de cada passo (±1) vem de
 * SIGN(dx)/SIGN(dy). Assim, um único laço cobre todos os octantes e
 * também os casos degenerados (linhas horizontais, verticais e pontos).
 *
 * @param canvas Canvas alvo.
 * @param a      Ponto inicial do segmento.
 * @param b      Ponto final do segmento.
 * @param color  Cor RGBA do traço.
 * @return Nenhum.
 *
 * @note O laço executa major_delta + 1 iterações, garantindo que ambos os
 *       extremos do segmento sejam pintados (segmento fechado).
 * @note Complexidade O(max(|dx|, |dy|)), com custo constante por pixel e
 *       sem nenhuma operação em ponto flutuante no laço.
 */
void draw_line(Canvas *canvas, Vec2 *a, Vec2 *b, uint32_t color)
{
	int x0, y0, x1, y1;
	int *major_coord, *minor_coord;
	int major_delta, minor_delta;
	int major_step, minor_step;

	x0 = a->x;
	y0 = a->y;
	x1 = b->x;
	y1 = b->y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	int x = x0;
	int y = y0;

	if (ABS(dx) > ABS(dy)) {
		major_coord = &x;
		minor_coord = &y;
		major_delta = ABS(dx);
		minor_delta = ABS(dy);
		major_step = SIGN(dx);
		minor_step = SIGN(dy);
	} else {
		major_coord = &y;
		minor_coord = &x;
		major_delta = ABS(dy);
		minor_delta = ABS(dx);
		major_step = SIGN(dy);
		minor_step = SIGN(dx);
	}

	int err = 2 * minor_delta - major_delta;

	for (int step = 0; step <= major_delta; step++) {
		Vec2 point = { x, y };

		draw_point(canvas, &point, color);

		if (err >= 0) {
			*minor_coord += minor_step;
			err -= 2 * major_delta;
		}

		*major_coord += major_step;
		err += 2 * minor_delta;
	}
}

/**
 * @brief Desenha apenas o contorno de um triângulo, ligando seus três
 *        vértices com segmentos de Bresenham.
 *
 * @param canvas   Canvas alvo.
 * @param triangle Triângulo a contornar.
 * @param color    Cor RGBA do contorno.
 * @return Nenhum.
 */
void draw_triangle(Canvas *canvas, Triangle *triangle, uint32_t color)
{
	Vec2 v[3] = { triangle->a, triangle->b, triangle->c };

	draw_line(canvas, &v[0], &v[1], color);
	draw_line(canvas, &v[0], &v[2], color);
	draw_line(canvas, &v[1], &v[2], color);
}

/**
 * @brief Preenche um triângulo pelo algoritmo de varredura (scanline fill).
 *
 * **Ideia central:** qualquer triângulo pode ser preenchido percorrendo-o
 * linha horizontal por linha horizontal (scanlines). Em cada linha y, a
 * área interna é delimitada por exatamente duas bordas do triângulo; basta
 * conhecer as interseções esquerda (xl) e direita (xr) e traçar a corda
 * horizontal entre elas.
 *
 * **Interpolação incremental:** em vez de resolver a interseção
 * reta-scanline a cada linha, calcula-se a *inclinação inversa* de cada
 * aresta (slope = dx/dy, ou seja, quanto x varia por unidade de y). A cada
 * scanline, xl e xr são simplesmente incrementados por sl e sr — uma soma
 * por borda por linha, no espírito dos algoritmos incrementais de
 * rasterização (mesma filosofia do termo de erro de Bresenham).
 *
 * **Estratégia de duas metades:** os vértices são ordenados por y
 * (v0 = topo, v1 = meio, v2 = base) com uma rede de trocas. O triângulo é
 * então varrido em duas fases: de v0.y até v1.y e de v1.y até v2.y. Na
 * transição, a aresta que terminou em v1 é substituída pela aresta v1→v2
 * (troca de sl ou sr), pois o lado correspondente do triângulo muda de
 * suporte. Os casos especiais de topo plano (y01 == 0) e base plana
 * (y12 == 0) são tratados separadamente para evitar divisão por zero no
 * cálculo da inclinação da aresta horizontal.
 *
 * @param canvas   Canvas alvo.
 * @param triangle Triângulo a preencher.
 * @param color    Cor RGBA de preenchimento.
 * @return Nenhum.
 *
 * @note Os vértices são arredondados (roundf) antes da varredura para
 *       alinhar as bordas à grade de pixels e evitar fissuras (cracks)
 *       entre triângulos adjacentes que compartilham arestas — importante
 *       porque retângulos e polígonos são desenhados como pares/leques de
 *       triângulos.
 * @note Complexidade O(altura * largura média das cordas), proporcional à
 *       área rasterizada — assintoticamente ótimo para preenchimento.
 */
void draw_fill_triangle(Canvas *canvas, Triangle *triangle, uint32_t color)
{
	Vec2 v[3] = { triangle->a, triangle->b, triangle->c };

	v[0].x = roundf(v[0].x); v[0].y = roundf(v[0].y);
	v[1].x = roundf(v[1].x); v[1].y = roundf(v[1].y);
	v[2].x = roundf(v[2].x); v[2].y = roundf(v[2].y);

	if (v[1].y < v[0].y) {
		Vec2 t = v[0];
		v[0] = v[1];
		v[1] = t;
	}
	if (v[2].y < v[0].y) {
		Vec2 t = v[0];
		v[0] = v[2];
		v[2] = t;
	}
	if (v[2].y < v[1].y) {
		Vec2 t = v[1];
		v[1] = v[2];
		v[2] = t;
	}

	float x0 = v[0].x, y0 = v[0].y;
	float x1 = v[1].x, y1 = v[1].y;
	float x2 = v[2].x, y2 = v[2].y;

	float x01 = x1 - x0, y01 = y1 - y0;
	float x02 = x2 - x0, y02 = y2 - y0;
	float x12 = x2 - x1, y12 = y2 - y1;

	float slope01, slope02, slope12;
	float xl, xr;
	float sl, sr;

	if (y01 == 0) {
		slope01 = 0.0f;
		slope02 = x02 / y02;
		slope12 = x12 / y12;

		xl = MIN(x0, x1);
		xr = MAX(x0, x1);

		sl = (x0 < x1) ? slope02 : slope12;
		sr = (x0 < x1) ? slope12 : slope02;
	} else if (y12 == 0) {
		slope01 = x01 / y01;
		slope02 = x02 / y02;
		slope12 = 0.0f;

		xl = x0;
		xr = x0;

		sl = MIN(slope01, slope02);
		sr = MAX(slope01, slope02);
	} else {
		slope01 = x01 / y01;
		slope02 = x02 / y02;
		slope12 = x12 / y12;

		xl = x0;
		xr = x0;

		sl = MIN(slope01, slope02);
		sr = MAX(slope01, slope02);
	}

	for (float y = v[0].y; y < v[1].y; y += 1.0f) {
		Vec2 a = { xl, y };
		Vec2 b = { xr, y };

		draw_line(canvas, &a, &b, color);

		xl += sl;
		xr += sr;
	}

	if (y01 != 0 && y12 != 0) {
		if (sl == slope01) {
			sl = slope12;
		} else {
			sr = slope12;
		}
	}

	for (float y = v[1].y; y <= v[2].y; y += 1.0f) {
		Vec2 a = { xl, y };
		Vec2 b = { xr, y };

		draw_line(canvas, &a, &b, color);

		xl += sl;
		xr += sr;
	}
}

/**
 * @brief Desenha um segmento com espessura como um quadrilátero orientado
 *        decomposto em dois triângulos preenchidos.
 *
 * **Construção geométrica:** dada a direção da linha d = (dx, dy), o vetor
 * perpendicular é obtido pela rotação de 90° (-dy, dx) — propriedade
 * direta da matriz de rotação. Esse perpendicular é normalizado (dividido
 * pelo seu comprimento, via Teorema de Pitágoras) para virar um vetor
 * unitário n, e então escalado por metade da espessura. Deslocando os dois
 * extremos da linha por +o e -o (o = n * thick/2), obtêm-se os quatro
 * cantos de um retângulo rotacionado cujo eixo central é o segmento
 * original. O retângulo é rasterizado como dois triângulos, reaproveitando
 * o scanline fill.
 *
 * @param canvas Canvas alvo.
 * @param a      Ponto inicial do eixo da linha.
 * @param b      Ponto final do eixo da linha.
 * @param thick  Espessura total, em pixels (metade para cada lado do eixo).
 * @param color  Cor RGBA.
 * @return Nenhum.
 *
 * @warning Se @p a e @p b coincidirem, len == 0 e a normalização divide
 *          por zero (resultado NaN). O chamador deve evitar segmentos
 *          degenerados.
 */
void draw_thick_line(Canvas *canvas, Vec2 *a, Vec2 *b, float thick, uint32_t color)
{
	float x0 = a->x;
	float y0 = a->y;
	float x1 = b->x;
	float y1 = b->y;

	float dx = x1 - x0;
	float dy = y1 - y0;

	Vec2 d = { -dy, dx };

	float len = sqrtf(d.x * d.x + d.y * d.y);

	Vec2 n = { d.x / len, d.y / len };

	float half = thick * 0.5f;

	Vec2 o = { n.x * half, n.y * half };

	Vec2 p0 = { x0 + o.x, y0 + o.y };
	Vec2 p1 = { x0 - o.x, y0 - o.y };
	Vec2 p2 = { x1 + o.x, y1 + o.y };
	Vec2 p3 = { x1 - o.x, y1 - o.y };

	Triangle t[2] = {
		{ p0, p2, p3 },
		{ p0, p1, p3 }
	};

	for (int i = 0; i < 2; i++) {
		draw_fill_triangle(canvas, &t[i], color);
	}
}

/**
 * @brief Desenha a circunferência pelo algoritmo do ponto médio
 *        (variante de Bresenham para círculos).
 *
 * **Por que apenas um octante?** A circunferência x² + y² = r² possui
 * simetria de reflexão em relação aos eixos e às diagonais. Calculando os
 * pixels de UM octante (de x = 0 até x == y, ou seja, o arco de 45°), os
 * outros sete são obtidos de graça pelas 8 combinações de sinais e trocas
 * (±x, ±y) e (±y, ±x) — reduzindo o trabalho a 1/8 do perímetro.
 *
 * **Critério de decisão (ponto médio):** ao avançar x em 1, é preciso
 * decidir se y permanece ou decrementa. O teste avalia se o *ponto médio*
 * vertical entre as duas opções, (x, y - 1/2), já caiu fora do círculo,
 * substituindo na equação implícita: x² + (y - 1/2)² > r². Multiplicando
 * tudo por 4 — daí o `4*x*x + (2*y - 1)² > 4*r*r` do código — eliminam-se
 * as frações e o teste fica inteiramente em aritmética inteira, sem raiz
 * quadrada nem trigonometria, fiel ao algoritmo clássico.
 *
 * @param canvas Canvas alvo.
 * @param circle Círculo (centro e raio) a desenhar.
 * @param color  Cor RGBA do contorno.
 * @return Nenhum.
 *
 * @note O laço `while (x <= y)` percorre exatamente o segundo octante;
 *       o vetor @c points materializa as 8 reflexões simétricas em torno
 *       do centro (cx, cy).
 */
void draw_circle(Canvas *canvas, Circle *circle, uint32_t color)
{
	int cx = circle->center.x;
	int cy = circle->center.y;
	int r = circle->radius;

	int x = 0;
	int y = r;

	while (x <= y) {
		int y_mid = 2 * y - 1;

		if (4 * x * x + y_mid * y_mid > 4 * r * r) {
			y--;
		}

		Vec2 points[] = {
			{ cx + x, cy + y },
			{ cx + x, cy - y },
			{ cx - x, cy + y },
			{ cx - x, cy - y },
			{ cx + y, cy + x },
			{ cx + y, cy - x },
			{ cx - y, cy + x },
			{ cx - y, cy - x }
		};

		for (int i = 0; i < 8; i++) {
			draw_point(canvas, &points[i], color);
		}

		x++;
	}
}

/**
 * @brief Desenha uma circunferência espessa como uma série de anéis
 *        concêntricos de raio decrescente.
 *
 * A espessura é obtida desenhando @p thick + 1 circunferências do ponto
 * médio, do raio original até (raio - thick), preenchendo o anel de dentro
 * para fora a partir da borda externa.
 *
 * @param canvas Canvas alvo.
 * @param circle Círculo de referência (define a borda EXTERNA do anel).
 * @param thick  Espessura do anel, em pixels.
 * @param color  Cor RGBA.
 * @return Nenhum.
 *
 * @note Como cada anel é rasterizado de forma independente, espessuras
 *       grandes podem exibir pequenos furos entre anéis vizinhos em
 *       regiões de alta curvatura (limitação conhecida da técnica de
 *       círculos concêntricos).
 */
void draw_thick_circle(Canvas *canvas, Circle *circle, float thick, uint32_t color)
{
	for (float t = 0; t <= thick; t += 1.0f) {
		Circle c = { circle->center, circle->radius - t };
		draw_circle(canvas, &c, color);
	}
}

/**
 * @brief Preenche um disco reutilizando o gerador de pontos do algoritmo
 *        do ponto médio para emitir cordas entre pontos simétricos.
 *
 * Em vez de pintar os 8 pontos simétricos isoladamente (como no contorno),
 * cada par de pontos espelhados horizontalmente é conectado por uma linha:
 * as cordas (cx - x → cx + x) e (cx - y → cx + y) nas alturas
 * correspondentes cobrem todo o interior do disco conforme o octante é
 * percorrido. Assim, o preenchimento herda a robustez e a aritmética
 * inteira do algoritmo do ponto médio.
 *
 * @param canvas Canvas alvo.
 * @param circle Círculo a preencher.
 * @param color  Cor RGBA de preenchimento.
 * @return Nenhum.
 *
 * @note Algumas cordas são traçadas mais de uma vez (sobreposição entre os
 *       grupos de simetria) — redundância inofensiva para cor sólida, pois
 *       reescrever um pixel com a mesma cor é idempotente.
 */
void draw_fill_circle(Canvas *canvas, Circle *circle, uint32_t color)
{
	int cx = circle->center.x;
	int cy = circle->center.y;
	int r = circle->radius;

	int x = 0;
	int y = r;

	while (x <= y) {
		int y_mid = 2 * y - 1;

		if (4 * x * x + y_mid * y_mid > 4 * r * r) {
			y--;
		}

		Vec2 lines[4][2] = {
			{ { cx + x, cy + y}, { cx - x, cy + y } },
			{ { cx + x, cy - y}, { cx - x, cy - y } },
			{ { cx + y, cy + x}, { cx - y, cy + x } },
			{ { cx + y, cy - x}, { cx - y, cy - x } }
		};

		for (int i = 0; i < 4; i++) {
			draw_line(canvas, &lines[i][0], &lines[i][1], color);
		}

		x++;
	}
}

/**
 * @brief Desenha o contorno de um retângulo com espessura mínima.
 *
 * Implementado como caso particular de draw_thick_rect() com thick = 0,
 * evitando duplicação da lógica de construção das quatro arestas.
 *
 * @param canvas Canvas alvo.
 * @param rect   Retângulo a contornar.
 * @param color  Cor RGBA do contorno.
 * @return Nenhum.
 */
void draw_rect(Canvas *canvas, Rect *rect, uint32_t color)
{
	draw_thick_rect(canvas, rect, 0.0f, color);
}

/**
 * @brief Desenha o contorno de um retângulo com espessura configurável.
 *
 * As quatro arestas são desenhadas como linhas espessas. Para que os
 * cantos fiquem fechados (sem o "degrau" que surgiria se cada aresta
 * terminasse exatamente no vértice), as arestas horizontais são estendidas
 * em meia espessura (half) para cada lado, e as verticais idem — assim os
 * quadriláteros das arestas se sobrepõem nos cantos formando junções
 * sólidas.
 *
 * @param canvas Canvas alvo.
 * @param rect   Retângulo a contornar.
 * @param thick  Espessura do traço, em pixels.
 * @param color  Cor RGBA.
 * @return Nenhum.
 *
 * @note O traço é centralizado sobre o perímetro geométrico do retângulo
 *       (metade da espessura para dentro, metade para fora).
 */
void draw_thick_rect(Canvas *canvas, Rect *rect, float thick, uint32_t color)
{
	int x = rect->pos.x;
	int y = rect->pos.y;
	int w = rect->size.x;
	int h = rect->size.y;
	float half = thick * 0.5f;

	Vec2 lines[4][2] = {
		{ { x - half, y }, { x + w - 1 + half, y } },
		{ { x - half, y + h - 1 }, { x + w - 1 + half, y + h - 1 } },
		{ { x, y - half }, { x, y + h - 1 + half } },
		{ { x + w - 1, y - half }, { x + w - 1, y + h - 1 + half } }
	};

	for (int i = 0; i < 4; i++) {
		draw_thick_line(canvas, &lines[i][0], &lines[i][1], thick, color);
	}
}

/**
 * @brief Preenche um retângulo decompondo-o na diagonal em dois triângulos.
 *
 * O retângulo (a, b, c, d) é dividido pela diagonal a–c nos triângulos
 * (a, b, c) e (a, c, d), ambos rasterizados pelo scanline fill. Essa
 * decomposição mantém o triângulo como única primitiva de preenchimento
 * do sistema.
 *
 * @param canvas Canvas alvo.
 * @param rect   Retângulo a preencher.
 * @param color  Cor RGBA de preenchimento.
 * @return Nenhum.
 *
 * @note Os cantos usam (x + w - 1, y + h - 1) porque, em coordenadas de
 *       pixel, um retângulo de largura w cobre as colunas x .. x+w-1
 *       (índices inclusivos).
 */
void draw_fill_rect(Canvas *canvas, Rect *rect, uint32_t color)
{
	float x = rect->pos.x;
	float y = rect->pos.y;
	float w = rect->size.x;
	float h = rect->size.y;

	Vec2 a = { x, y };
	Vec2 b = { x + w - 1, y };
	Vec2 c = { x + w - 1, y + h - 1 };
	Vec2 d = { x, y + h - 1 };

	Triangle t1 = { a, b, c };
	Triangle t2 = { a, c, d };

	draw_fill_triangle(canvas, &t1, color);
	draw_fill_triangle(canvas, &t2, color);
}

/**
 * @brief Desenha o contorno de um polígono fechado.
 *
 * Liga cada vértice ao seguinte com segmentos de Bresenham; o operador
 * módulo no índice ((i + 1) % num_points) faz o último vértice conectar-se
 * de volta ao primeiro, fechando o polígono sem caso especial.
 *
 * @param canvas     Canvas alvo.
 * @param points     Vetor de vértices em ordem (horária ou anti-horária).
 * @param num_points Número de vértices.
 * @param color      Cor RGBA do contorno.
 * @return Nenhum.
 */
void draw_polygon(Canvas *canvas, Vec2 *points, int num_points, uint32_t color)
{
	for (int i = 0; i < num_points; i++) {
		draw_line(canvas, &points[i], &points[(i + 1) % num_points], color);
	}
}

/**
 * @brief Preenche um polígono por triangulação em leque (fan triangulation).
 *
 * Fixa o vértice 0 como pivô e gera os triângulos (p0, p1, p2),
 * (p0, p2, p3), ..., (p0, p[n-2], p[n-1]). Para polígonos CONVEXOS, a
 * união desses n-2 triângulos cobre exatamente a área do polígono — é a
 * decomposição mais simples possível, e novamente reduz tudo ao scanline
 * fill de triângulos.
 *
 * @param canvas     Canvas alvo.
 * @param points     Vetor de vértices em ordem.
 * @param num_points Número de vértices.
 * @param color      Cor RGBA de preenchimento.
 * @return Nenhum.
 *
 * @warning Válido apenas para polígonos convexos: em polígonos côncavos o
 *          leque a partir de p0 gera triângulos que extrapolam a área real.
 */
void draw_fill_polygon(Canvas *canvas, Vec2 *points, int num_points, uint32_t color)
{
	for (int i = 1; i < num_points - 1; i++) {
		Triangle t = { points[0], points[i], points[i + 1] };
		draw_fill_triangle(canvas, &t, color);
	}
}

/**
 * @brief Colisão ponto-retângulo: teste de pertencimento a um AABB.
 *
 * Um ponto está dentro de um retângulo alinhado aos eixos se, e somente
 * se, suas coordenadas estão simultaneamente dentro dos intervalos
 * horizontais e verticais do retângulo — duas comparações de intervalo
 * independentes, sem qualquer trigonometria.
 *
 * @param point Ponto a testar.
 * @param rect  Retângulo alinhado aos eixos.
 * @return @c true se o ponto pertence ao retângulo; @c false caso contrário.
 *
 * @note Intervalos semiabertos [pos, pos + size): a borda superior/esquerda
 *       conta como "dentro" e a inferior/direita como "fora", garantindo
 *       partição exata do plano entre retângulos adjacentes (sem pixels
 *       pertencendo a dois ao mesmo tempo). Usado, por exemplo, para
 *       detectar cliques em botões/áreas da interface.
 */
bool point_in_rect(Vec2 *point, Rect *rect)
{
	return (
			rect->pos.x <= point->x && point->x < (rect->pos.x + rect->size.x) &&
			rect->pos.y <= point->y && point->y < (rect->pos.y + rect->size.y)
	       );
}

/**
 * @brief Colisão ponto-círculo via distância euclidiana ao quadrado.
 *
 * O ponto está dentro do círculo se sua distância ao centro é menor ou
 * igual ao raio. Como a raiz quadrada é cara e desnecessária — elevar ao
 * quadrado preserva a ordem para valores não negativos — compara-se
 * diretamente dx² + dy² <= r². É a otimização padrão de detecção de
 * colisão em jogos, executada potencialmente milhares de vezes por frame.
 *
 * @param point  Ponto a testar.
 * @param circle Círculo de referência.
 * @return @c true se o ponto está dentro ou sobre a borda do círculo.
 */
bool point_in_circle(Vec2 *point, Circle *circle)
{
	float x_diff = point->x - circle->center.x;
	float y_diff = point->y - circle->center.y;
	float r_square = circle->radius * circle->radius;

	return x_diff * x_diff + y_diff * y_diff <= r_square;
}

/**
 * @brief Testa se um círculo está completamente FORA de um retângulo.
 *
 * Aplica o princípio do eixo separador ao AABB do círculo: se o intervalo
 * horizontal [cx - r, cx + r] não intersecta [rx, rx + rw], OU o intervalo
 * vertical [cy - r, cy + r] não intersecta [ry, ry + rh], então existe um
 * eixo que separa as duas formas e não há contato possível.
 *
 * @param circle Círculo a testar.
 * @param rect   Retângulo de referência (ex.: limites da tela/arena).
 * @return @c true se o círculo está inteiramente fora do retângulo.
 *
 * @note Por usar o AABB do círculo (e não o círculo exato), o teste é
 *       conservador: @c false não garante interseção real nos cantos, mas
 *       @c true garante separação — ideal como rejeição rápida ou para
 *       detectar que um objeto saiu da área de jogo.
 */
bool circle_out_rect(Circle *circle, Rect *rect)
{
	float cx = circle->center.x;
	float cy = circle->center.y;
	float r = circle->radius;
	float rx = rect->pos.x;
	float ry = rect->pos.y;
	float rw = rect->size.x;
	float rh = rect->size.y;

	bool out_x = (cx + r) < rx || (rx + rw) < (cx - r);
	bool out_y = (cy + r) < ry || (ry + rh) < (cy - r);

	return out_x || out_y;
}

/**
 * @brief Colisão círculo-círculo.
 *
 * Dois círculos se tocam ou se sobrepõem se, e somente se, a distância
 * entre seus centros é menor ou igual à SOMA dos raios. Tal como em
 * point_in_circle(), a comparação é feita ao quadrado
 * (dx² + dy² <= (r1 + r2)²) para eliminar a raiz quadrada do caminho
 * crítico da detecção de colisão do jogo.
 *
 * @param c1 Primeiro círculo.
 * @param c2 Segundo círculo.
 * @return @c true se há contato ou sobreposição entre os círculos.
 *
 * @note Este é o teste de colisão mais barato entre formas com rotação
 *       livre, pois círculos são invariantes à rotação — motivo pelo qual
 *       é amplamente usado como volume de colisão em jogos 2D.
 */
bool circle_in_circle(Circle *c1, Circle *c2)
{
	float dx = c2->center.x - c1->center.x;
	float dy = c2->center.y - c1->center.y;
	float r  = c1->radius + c2->radius;

	return dx * dx + dy * dy <= r * r;
}
