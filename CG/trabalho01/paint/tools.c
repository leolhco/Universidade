/**
 * @file tools.c
 * @brief Implementação de todas as ferramentas do Mini Paint e do flood fill iterativo.
 *
 * Define as 8 ferramentas exigidas pelo enunciado do Trabalho 1 — lápis,
 * borracha, linha, retângulo vazado, retângulo cheio, círculo vazado,
 * círculo cheio e balde de tinta — como instâncias da estrutura @c Tool
 * (ver tools.h). Cada uma é apenas um conjunto de callbacks
 * (@c draw_icon, @c on_click, @c on_motion, @c on_release) que delegam
 * o desenho às primitivas próprias do projeto (Bresenham, ponto médio,
 * scanline fill).
 *
 * Inclui também a implementação do **flood fill iterativo com pilha
 * explícita** (função @c flood_fill), peça central avaliada pelo
 * critério "Algoritmos de rasterização sem trapaça". O enunciado pede
 * literalmente: "Flood fill recursivo ou com pilha/queue (não usar
 * função pronta)". Aqui se optou pela variante iterativa, mais robusta
 * em canvases grandes (evita estouro da pilha de chamadas do C).
 *
 * @note Nenhuma ferramenta chama funções de desenho da SDL. Todas usam
 *       apenas as primitivas implementadas em shapes.c (Bresenham,
 *       ponto médio, scanline) operando sobre o framebuffer @c app.art.
 */

#include "shapes.h"
#include "canvas.h"
#include "color.h"
#include <stddef.h>
#include <math.h>
#include "paint.h"
#include "tools.h"

#include <stdlib.h>

/** @brief Referência ao estado global, definido em paint.c. */
extern App app;

/* === Protótipos internos (forward declarations) ===
 * Cada ferramenta possui até 4 funções estáticas: o renderizador do
 * ícone na toolbar e os callbacks de clique/motion/release. Mantê-las
 * @c static deixa o escopo restrito ao módulo. */

static void pencil_icon(Rect *bounds);
static void pencil_on_click();
static void pencil_on_motion();

static void eraser_icon(Rect *bounds);
static void eraser_on_click();
static void eraser_on_motion();

static void line_icon(Rect *bounds);
static void line_on_release();

static void rect_icon(Rect *bounds);
static void rect_on_release();

static void rect_fill_icon(Rect *bounds);
static void rect_fill_on_release();

static void circle_icon(Rect *bounds);
static void circle_on_release();

static void circle_fill_icon(Rect *bounds);
static void circle_fill_on_release();

static void bucket_icon(Rect *bounds);
static void bucket_on_click();

/**
 * @brief Ferramenta Lápis: pincel a mão livre de 1 pixel ou mais.
 * @note @c preview = @c false → desenha diretamente, sem snapshot/restore.
 */
Tool pencil = {
	.preview = false,
	.draw_icon = pencil_icon,
	.on_click = pencil_on_click,
	.on_motion = pencil_on_motion,
	.on_release = NULL
};

/**
 * @brief Ferramenta Borracha: pinta com a cor de fundo (branco) — mesma lógica do lápis.
 */
Tool eraser = {
	.preview = false,
	.draw_icon = eraser_icon,
	.on_click = eraser_on_click,
	.on_motion = eraser_on_motion,
	.on_release = NULL
};

/**
 * @brief Ferramenta Linha (Bresenham).
 * @note @c preview = @c true → durante o arrasto, a linha é redesenhada a
 *       partir do snapshot a cada quadro, criando o efeito de "elástico".
 *       @c on_motion e @c on_release apontam para a MESMA função para
 *       garantir que a linha final seja idêntica ao preview.
 */
Tool line = {
	.preview = true,
	.draw_icon = line_icon,
	.on_click = NULL,
	.on_motion = line_on_release,
	.on_release = line_on_release
};

/**
 * @brief Ferramenta Retângulo vazado (apenas contorno).
 */
Tool rect = {
	.preview = true,
	.draw_icon = rect_icon,
	.on_click = NULL,
	.on_motion = rect_on_release,
	.on_release = rect_on_release
};

/**
 * @brief Ferramenta Retângulo cheio (preenchido por dois triângulos via scanline fill).
 */
Tool rect_fill = {
	.preview = true,
	.draw_icon = rect_fill_icon,
	.on_click = NULL,
	.on_motion = rect_fill_on_release,
	.on_release = rect_fill_on_release
};

/**
 * @brief Ferramenta Círculo vazado (algoritmo do ponto médio com simetria de 8 octantes).
 */
Tool circle = {
	.preview = true,
	.draw_icon = circle_icon,
	.on_click = NULL,
	.on_motion = circle_on_release,
	.on_release = circle_on_release
};

/**
 * @brief Ferramenta Círculo cheio (preenchimento por cordas geradas pelo ponto médio).
 */
Tool circle_fill = {
	.preview = true,
	.draw_icon = circle_fill_icon,
	.on_click = NULL,
	.on_motion = circle_fill_on_release,
	.on_release = circle_fill_on_release
};

/**
 * @brief Ferramenta Balde de tinta (flood fill iterativo 4-conectado).
 * @note Como o preenchimento se completa em um único @c on_click, a
 *       ferramenta não usa preview nem callbacks de motion/release.
 */
Tool bucket = {
	.preview = false,
	.draw_icon = bucket_icon,
	.on_click = bucket_on_click,
	.on_motion = NULL,
	.on_release = NULL
};

/**
 * @brief Vetor com as @c NUM_TOOLS ferramentas, na ordem em que aparecem na toolbar.
 */
Tool *tools[] = {
	&pencil,
	&eraser,
	&line,
	&rect,
	&rect_fill,
	&circle,
	&circle_fill,
	&bucket
};

/**
 * @brief Desenha o ícone do lápis na toolbar (varredura horizontal por linhas).
 *
 * O ícone é montado por bandas horizontais (laço sobre @c i = linha y do
 * ícone), cada banda preenchida com uma cor diferente — ponta, madeira,
 * grafite. Como o módulo só dispõe de @c draw_line para encher pixels, a
 * silhueta é desenhada uma scanline por vez.
 *
 * @param bounds Retângulo do botão da ferramenta na toolbar.
 * @return Nenhum.
 */
void pencil_icon(Rect *bounds)
{
	float mx = bounds->size.x / 5.0f;
	float my = bounds->size.y / 5.0f;

	float x = bounds->pos.x + mx;
	float y = bounds->pos.y + my;
	float w = bounds->size.x - 2.0f * mx;
	float h = bounds->size.y - 2.0f * my;

	float side = (w < h) ? w : h;
	float sx = x + (w - side) * 0.5f;
	float sy = y + (h - side) * 0.5f;

	float x_pencil = sx + side * 1.0f / 3.0f;
	float y_pencil = sy;
	float w_pencil = side * 1.0f / 3.0f;
	float h_pencil = side;

	for (int i = 0; i < 2.0f / 6.0f * h_pencil; i++) {
		Vec2 a = { x_pencil + w_pencil * 0.5f + i * 0.5f * w_pencil / (2.0f / 6.0f * h_pencil), y_pencil + i };
		Vec2 b = { x_pencil + w_pencil * 0.5f - i * 0.5f * w_pencil / (2.0f / 6.0f * h_pencil), y_pencil + i };

		if (i < 0.5f * 2.0f / 6.0f * h_pencil) {
			draw_line(app.screen, &a, &b, MAROON);
		} else {
			draw_line(app.screen, &a, &b, LIGHTPINK);
		}
	}

	for (int i = 2.0f / 6.0f * h_pencil; i < 5.0f / 6.0f * h_pencil; i++) {
		Vec2 a = { x_pencil, y_pencil + i };
		Vec2 b = { x_pencil + w_pencil, y_pencil + i };

		if (i < 2.0f / 6.0f * h_pencil + 5.0f / 6.0f * h_pencil / 10.0f) {
			draw_line(app.screen, &a, &b, LIGHTGREY);
		} else {
			draw_line(app.screen, &a, &b, DARKORANGE);
		}
	}

	for (int i = 5.0f / 6.0f * h_pencil; i < h_pencil - 1; i++) {
		Vec2 a = { x_pencil, y_pencil + i };
		Vec2 b = { x_pencil + w_pencil, y_pencil + i };

		if (i < 5.0f / 6.0f * h_pencil + 0.5f * h_pencil / 6.0f) {
			draw_line(app.screen, &a, &b, DARKGREY);
		} else {
			draw_line(app.screen, &a, &b, HOTPINK);
		}
	}

	pencil.bounds = *bounds;
}

/**
 * @brief Callback de clique do lápis: pinta um único ponto/círculo na posição do mouse.
 *
 * @c THIN = 1 pixel é tratado como caso especial: usa draw_point()
 * diretamente, evitando o custo desnecessário de draw_fill_circle() com
 * raio 0.5 — um exemplo de otimização do caminho crítico do desenho a
 * mão livre.
 *
 * @return Nenhum.
 */
void pencil_on_click()
{
	if (app.thickness == THIN) {
		draw_point(app.art, &app.art_curr, app.color);
	} else {
		draw_fill_circle(app.art, &(Circle){ app.art_curr, app.thickness * 0.5f }, app.color);
	}
}

/**
 * @brief Callback de motion do lápis: conecta a posição anterior à atual com um segmento.
 *
 * Sem essa conexão, movimentos rápidos do mouse produziriam um traço
 * pontilhado, pois SDL_MOUSEMOTION é amostrado discretamente e pode
 * "saltar" vários pixels entre eventos. Ligando @c art_prev a
 * @c art_curr com draw_line() (Bresenham) o traço fica contínuo
 * independentemente da velocidade do mouse.
 *
 * @return Nenhum.
 */
void pencil_on_motion()
{
	if (app.thickness == THIN) {
		draw_line(app.art, &app.art_curr, &app.art_prev, app.color);
	} else {
		draw_thick_line(app.art, &app.art_curr, &app.art_prev, app.thickness, app.color);
	}
}

/**
 * @brief Desenha o ícone da borracha (paralelogramo angulado com duas faces).
 *
 * Os pontos p0..p5 são construídos por interpolação linear:
 * w0 = p0 + t·(p3 - p0) e w1 = p1 + t·(p2 - p1) marcam a "linha de
 * cisalhamento" entre o topo da borracha (rosa) e o corpo lateral
 * (cinza), simulando perspectiva.
 *
 * @param bounds Retângulo do botão da ferramenta.
 * @return Nenhum.
 */
void eraser_icon(Rect *bounds)
{
	float mx = bounds->size.x / 5.0f;
	float my = bounds->size.y / 5.0f;

	float x = bounds->pos.x + mx;
	float y = bounds->pos.y + my;
	float w = bounds->size.x - 2.0f * mx;
	float h = bounds->size.y - 2.0f * my;

	float side = (w < h) ? w : h;
	float sx = x + (w - side) * 0.5f;
	float sy = y + (h - side) * 0.5f;

	Vec2 p0 = { sx, sy + 0.75f * side };
	Vec2 p1 = { sx + 0.25f * side, sy + side };

	float a = p1.x - sx;
	float b = p0.y - sy;

	Vec2 p2 = { sx + side, sy + side - b };
	Vec2 p3 = { sx + side - a, sy };

	float t = 0.65f;

	Vec2 p4 = { p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y) };
	Vec2 p5 = { p0.x + t * (p3.x - p0.x), p0.y + t * (p3.y - p0.y) };

	Vec2 bottom[] = { p0, p1, p4, p5 };
	Vec2 top[] = { p5, p3, p2, p4 };

	draw_fill_polygon(app.screen, top, 4, PINK);
	draw_fill_polygon(app.screen, bottom, 4, LIGHTGREY);
}

/**
 * @brief Borracha: clique único pinta com a cor de fundo (branco).
 *
 * Implementação idêntica à do lápis, mas com cor fixa em @c WHITE —
 * cumpre o requisito do enunciado: "Borracha (pinta com a cor de fundo)".
 *
 * @return Nenhum.
 */
void eraser_on_click()
{
	if (app.thickness == THIN) {
		draw_point(app.art, &app.art_curr, WHITE);
	} else {
		draw_fill_circle(app.art, &(Circle){ app.art_curr, app.thickness * 0.5f }, WHITE);
	}
}

/**
 * @brief Borracha em arrasto: mesma lógica do lápis com cor branca.
 * @return Nenhum.
 */
void eraser_on_motion()
{
	if (app.thickness == THIN) {
		draw_line(app.art, &app.art_curr, &app.art_prev, WHITE);
	} else {
		draw_thick_line(app.art, &app.art_curr, &app.art_prev, app.thickness, WHITE);
	}
}

/**
 * @brief Desenha o ícone da ferramenta linha (segmento na diagonal do botão).
 * @param bounds Retângulo do botão.
 * @return Nenhum.
 */
void line_icon(Rect *bounds)
{
	float mx = bounds->size.x / 5.0f;
	float my = bounds->size.y / 5.0f;

	float x = bounds->pos.x + mx;
	float y = bounds->pos.y + my;
	float w = bounds->size.x - 2.0f * mx;
	float h = bounds->size.y - 2.0f * my;

	float side = (w < h) ? w : h;
	float sx = x + (w - side) * 0.5f;
	float sy = y + (h - side) * 0.5f;

	Vec2 a = { sx, sy };
	Vec2 b = { sx + side, sy + side };

	draw_thick_line(app.screen, &a, &b, 0.1f * w, BLACK);
	line.bounds = *bounds;
}

/**
 * @brief Linha: traça segmento entre o ponto inicial (@c art_start) e o atual (@c art_curr).
 *
 * Usada tanto em @c on_motion (preview elástico) quanto em @c on_release
 * (linha definitiva), apontadas para a MESMA função, garantindo
 * consistência entre o que o usuário vê durante o arrasto e o que fica
 * gravado no canvas ao soltar o botão. A primitiva subjacente é o
 * algoritmo de Bresenham (draw_line) ou sua versão espessa
 * (draw_thick_line, que reduz a linha grossa a dois triângulos por
 * scanline fill).
 *
 * @return Nenhum.
 */
void line_on_release()
{
	if (app.thickness == THIN) {
		draw_line(app.art, &app.art_start, &app.art_curr, app.color);
	} else {
		draw_thick_line(app.art, &app.art_start, &app.art_curr, app.thickness, app.color);
	}
}

/**
 * @brief Desenha o ícone do retângulo vazado.
 * @param bounds Retângulo do botão.
 * @return Nenhum.
 */
void rect_icon(Rect *bounds)
{
	float mx = bounds->size.x / 5.0f;
	float my = bounds->size.y / 5.0f;

	float x = bounds->pos.x + mx;
	float y = bounds->pos.y + my;
	float w = bounds->size.x - 2.0f * mx;
	float h = bounds->size.y - 2.0f * my;

	float side = (w < h) ? w : h;
	float sx = x + (w - side) * 0.5f;
	float sy = y + (h - side) * 0.5f;

	float x_rect = sx;
	float y_rect = sy;
	float w_rect = side;
	float h_rect = side;

	Vec2 pos = { x_rect, y_rect };
	Vec2 size = { w_rect, h_rect };
	Rect r = { pos, size };

	draw_rect(app.screen, &r, BLACK);

	rect.bounds = *bounds;
}

/**
 * @brief Retângulo vazado: normaliza os cantos e desenha o contorno com espessura.
 *
 * **Normalização dos cantos:** o usuário pode arrastar do canto
 * inferior-direito para o superior-esquerdo (ou qualquer outra
 * direção). Para que o retângulo final seja sempre construído com
 * @c pos = canto superior-esquerdo e @c size > 0, calcula-se
 * (xmin, ymin) e (xmax, ymax) a partir dos dois pontos de arrasto —
 * convertendo qualquer direção de arrasto no AABB equivalente.
 *
 * @return Nenhum.
 */
void rect_on_release()
{
	Vec2 *start = &app.art_start;
	Vec2 *curr = &app.art_curr;

	float x_max = start->x > curr->x ? start->x : curr->x;
	float x_min = start->x < curr->x ? start->x : curr->x;
	float y_max = start->y > curr->y ? start->y : curr->y;
	float y_min = start->y < curr->y ? start->y : curr->y;

	float x = x_min;
	float y = y_min;
	float w = x_max - x_min;
	float h = y_max - y_min;

	Vec2 pos = { x, y };
	Vec2 size = { w, h };
	Rect rect = { pos, size };

	draw_thick_rect(app.art, &rect, app.thickness, app.color);
}

/**
 * @brief Desenha o ícone do retângulo preenchido.
 * @param bounds Retângulo do botão.
 * @return Nenhum.
 */
void rect_fill_icon(Rect *bounds)
{
	float mx = bounds->size.x / 5.0f;
	float my = bounds->size.y / 5.0f;

	float x = bounds->pos.x + mx;
	float y = bounds->pos.y + my;
	float w = bounds->size.x - 2.0f * mx;
	float h = bounds->size.y - 2.0f * my;

	float side = (w < h) ? w : h;
	float sx = x + (w - side) * 0.5f;
	float sy = y + (h - side) * 0.5f;

	float x_rect = sx;
	float y_rect = sy;
	float w_rect = side;
	float h_rect = side;

	Vec2 pos = { x_rect, y_rect };
	Vec2 size = { w_rect, h_rect };
	Rect rect = { pos, size };

	draw_fill_rect(app.screen, &rect, BLACK);

	rect_fill.bounds = *bounds;
}

/**
 * @brief Retângulo preenchido: mesma normalização do vazado + scanline fill.
 *
 * Como @c draw_fill_rect decompõe o retângulo em dois triângulos
 * preenchidos por varredura (ver shapes.c), esta ferramenta exercita os
 * dois algoritmos exigidos no enunciado: traçado de linhas (cordas
 * horizontais do scanline) e preenchimento de polígonos.
 *
 * @return Nenhum.
 */
void rect_fill_on_release()
{
	Vec2 *start = &app.art_start;
	Vec2 *curr = &app.art_curr;

	float x_max = start->x > curr->x ? start->x : curr->x;
	float x_min = start->x < curr->x ? start->x : curr->x;
	float y_max = start->y > curr->y ? start->y : curr->y;
	float y_min = start->y < curr->y ? start->y : curr->y;

	float x = x_min;
	float y = y_min;
	float w = x_max - x_min;
	float h = y_max - y_min;

	Vec2 pos = { x, y };
	Vec2 size = { w, h };
	Rect rect = { pos, size };

	draw_fill_rect(app.art, &rect, app.color);
}

/**
 * @brief Desenha o ícone do círculo vazado.
 * @param bounds Retângulo do botão.
 * @return Nenhum.
 */
void circle_icon(Rect *bounds)
{
	float mx = bounds->size.x / 5.0f;
	float my = bounds->size.y / 5.0f;

	float x = bounds->pos.x + mx;
	float y = bounds->pos.y + my;
	float w = bounds->size.x - 2.0f * mx;
	float h = bounds->size.y - 2.0f * my;

	float side = (w < h) ? w : h;
	float sx = x + (w - side) * 0.5f;
	float sy = y + (h - side) * 0.5f;

	float cx = sx + side * 0.5f;
	float cy = sy + side * 0.5f;
	float r = (cx > cy) ? cy * 0.5f : cx * 0.5f;

	Vec2 center = { cx, cy };
	Circle c = { center, r };

	draw_circle(app.screen, &c, BLACK);

	circle.bounds = *bounds;
}

/**
 * @brief Círculo vazado: centro no ponto inicial, raio = distância até o ponto atual.
 *
 * O raio é calculado como a distância euclidiana entre @c art_start e
 * @c art_curr (Teorema de Pitágoras: sqrtf(dx² + dy²)). Aqui a raiz
 * quadrada é necessária (não é apenas comparação), por isso não cabe a
 * otimização de "comparar distâncias ao quadrado" usada nos testes de
 * colisão. O círculo é depois rasterizado pelo algoritmo do PONTO MÉDIO
 * com simetria de 8 octantes (ver draw_circle/draw_thick_circle em
 * shapes.c) — exatamente o algoritmo exigido pelo enunciado.
 *
 * @return Nenhum.
 */
void circle_on_release()
{
	Vec2 *start = &app.art_start;
	Vec2 *curr = &app.art_curr;

	Vec2 center = *start;
	float x_diff = start->x - curr->x;
	float y_diff = start->y - curr->y;
	float radius = sqrtf(x_diff * x_diff + y_diff * y_diff);

	Circle circle = { center, radius };
	
	draw_thick_circle(app.art, &circle, app.thickness, app.color);
}

/**
 * @brief Desenha o ícone do círculo preenchido.
 * @param bounds Retângulo do botão.
 * @return Nenhum.
 */
void circle_fill_icon(Rect *bounds)
{

	float mx = bounds->size.x / 5.0f;
	float my = bounds->size.y / 5.0f;

	float x = bounds->pos.x + mx;
	float y = bounds->pos.y + my;
	float w = bounds->size.x - 2.0f * mx;
	float h = bounds->size.y - 2.0f * my;

	float side = (w < h) ? w : h;
	float sx = x + (w - side) * 0.5f;
	float sy = y + (h - side) * 0.5f;

	float cx = sx + side * 0.5f;
	float cy = sy + side * 0.5f;
	float r = (cx > cy) ? cy * 0.5f : cx * 0.5f;

	Vec2 center = { cx, cy };
	Circle circle = { center, r };

	draw_fill_circle(app.screen, &circle, BLACK);

	circle_fill.bounds = *bounds;
}

/**
 * @brief Círculo preenchido: mesma lógica do vazado + preenchimento por cordas.
 *
 * @c draw_fill_circle (ver shapes.c) gera cordas horizontais entre
 * pares simétricos do algoritmo do ponto médio, varrendo o interior do
 * disco sem precisar testar pixel a pixel se está dentro do círculo.
 *
 * @return Nenhum.
 */
void circle_fill_on_release()
{
	Vec2 *start = &app.art_start;
	Vec2 *curr = &app.art_curr;
	
	Vec2 center = *start;
	float x_diff = start->x - curr->x;
	float y_diff = start->y - curr->y;
	float radius = sqrtf(x_diff * x_diff + y_diff * y_diff);

	Circle circle = { center, radius };
	
	draw_fill_circle(app.art, &circle, app.color);
}

/**
 * @brief Desenha o ícone do balde de tinta (corpo trapezoidal + alça + "água").
 * @param bounds Retângulo do botão.
 * @return Nenhum.
 */
static void bucket_icon(Rect *bounds)
{
	float mx = bounds->size.x / 5.0f;
	float my = bounds->size.y / 5.0f;

	float x = bounds->pos.x + mx;
	float y = bounds->pos.y + my;
	float w = bounds->size.x - 2.0f * mx;
	float h = bounds->size.y - 2.0f * my;

	float side = (w < h) ? w : h;
	float sx = x + (w - side) * 0.5f;
	float sy = y + (h - side) * 0.5f;

	float w_bucket = side - 0.15f * side;
	float x_bucket = sx + (side - w_bucket) * 0.5f;
	float h_bucket = 0.75f * side;
	float y_bucket = sy + side - h_bucket; 

	Vec2 p0 = { x_bucket, y_bucket };
	Vec2 p1 = { x_bucket + w_bucket, y_bucket };
	Vec2 p2 = { x_bucket + w_bucket - 0.2f * w_bucket, y_bucket + h_bucket };
	Vec2 p3 = { x_bucket + 0.2f * w_bucket, y_bucket + h_bucket };

	float t = 0.125f;

	Vec2 w0 = { p0.x + t * (p3.x - p0.x), p0.y + t * (p3.y - p0.y) };
	Vec2 w1 = { p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y) };

	Vec2 center = { (p0.x + p1.x) * 0.5f, (p0.y + p1.y) * 0.5f };
	float radius = w_bucket * 0.9f * 0.5f;

	Circle handle = { center, radius };

	Vec2 bucket[] = { p0, p1, p2, p3 };
	Vec2 water[]  = { p0, p1, w1, w0 };

	draw_circle(app.screen, &handle, BLACK);
	draw_fill_polygon(app.screen, bucket, 4, LIGHTGREY);
	draw_fill_polygon(app.screen, water, 4, BLUE);
}

/**
 * @brief Algoritmo de FLOOD FILL ITERATIVO 4-CONECTADO com pilha explícita
 *        e crescimento dinâmico (preenchimento por inundação).
 *
 * **O quê:** percorre a região conexa de pixels que compartilham a mesma
 * cor original do ponto inicial (@p x0, @p y0) e a substitui por
 * @p new_color. É a implementação do "Balde de tinta" exigida pelo
 * enunciado: "Flood fill recursivo ou com pilha/queue (NÃO USAR FUNÇÃO
 * PRONTA)".
 *
 * **Por que iterativo (e não recursivo)?** O flood fill recursivo é
 * elegante mas TÓXICO em canvases grandes: cada pixel adiciona um quadro
 * à pilha de chamadas do C, e canvases de algumas centenas de milhares
 * de pixels facilmente causam estouro de pilha. A versão iterativa
 * substitui a recursão por uma PILHA EXPLÍCITA em memória heap, que
 * cresce conforme necessário (realloc, dobrando a capacidade) e cuja
 * única limitação é a RAM disponível.
 *
 * **Por que 4-conectado e não 8?** O enunciado aceita as duas variantes.
 * O 4-conectado considera vizinhos apenas pelas arestas
 * (cima/baixo/esquerda/direita) — é o comportamento clássico do balde
 * de tinta do Microsoft Paint: regiões diagonais NÃO transbordam umas
 * para as outras, o que dá um resultado mais previsível para o usuário
 * em desenhos a mão livre, onde linhas finas de 1 pixel costumam
 * separar regiões.
 *
 * **Algoritmo em detalhe:**
 *  1. Lê a cor original (@c prev_color) do pixel inicial via
 *     canvas_get_pixel(). Se for igual à cor nova, há nada a fazer
 *     (otimização que evita laço infinito quando o usuário clica em
 *     uma região já pintada com a cor selecionada).
 *  2. Aloca uma pilha dinâmica com capacidade inicial 4 (cresce
 *     dobrando via realloc quando enche — amortização O(1) por push).
 *  3. Empilha o pixel inicial e PINTA-O ANTES de empilhar — esse
 *     "pinta antes de empilhar" é crucial: marca o pixel como
 *     visitado, evitando que ele seja empilhado uma segunda vez por
 *     um vizinho. Sem essa marcação, a pilha cresceria explosivamente.
 *  4. Enquanto a pilha não estiver vazia:
 *     - Desempilha o topo (ordem LIFO → expansão em profundidade).
 *     - Examina os 4 vizinhos (E, O, S, N).
 *     - Para cada vizinho dentro dos limites do canvas e com a cor
 *       ORIGINAL: pinta com @p new_color (marcação imediata) e empilha.
 *  5. Ao final, libera a pilha com free().
 *
 * @param x0        Coordenada x do ponto inicial (em coordenadas da arte).
 * @param y0        Coordenada y do ponto inicial.
 * @param new_color Cor RGBA com a qual preencher a região conexa.
 * @return Nenhum.
 *
 * @note A pilha é alocada no heap (via @c malloc / @c realloc) para que
 *       o estouro de pilha do C não seja um risco, independentemente do
 *       tamanho da região preenchida.
 * @note A verificação @c canvas_in_bounds() no início é uma guarda
 *       conservadora: se o usuário clicar fora da arte (improvável dada
 *       a verificação @c hit_art_area() no laço principal), a função
 *       retorna sem efeito.
 * @warning Se @p new_color == cor original do pixel inicial, a função
 *          retorna imediatamente — caso contrário entraria em laço
 *          infinito, pois os vizinhos nunca "trocariam" de cor após o
 *          pinte.
 */
static void flood_fill(int x0, int y0, uint32_t new_color)
{
	uint32_t prev_color = canvas_get_pixel(app.art, x0, y0);

	if (!canvas_in_bounds(app.art, x0, y0) || prev_color == new_color) {
		return;
	}

	int capacity = 4;
	int cp = 0;
	Vec2 *stack = malloc(sizeof(Vec2) * capacity);

	stack[cp++] = (Vec2){ x0, y0 };

	canvas_put_pixel(app.art, x0, y0, new_color);

	while (cp > 0) {
		Vec2 p = stack[--cp];

		int x = p.x;
		int y = p.y;

		Vec2 neighbors[] = {
			{ x + 1, y },
			{ x - 1, y },
			{ x, y + 1 },
			{ x, y - 1 }
		};

		for (int i = 0; i < 4; i++) {
			int nx = neighbors[i].x;
			int ny = neighbors[i].y;

			if (canvas_in_bounds(app.art, nx, ny) &&
					canvas_get_pixel(app.art, nx, ny) == prev_color) {
				canvas_put_pixel(app.art, nx, ny, new_color);

				if (cp >= capacity) {
					capacity *= 2;
					stack = realloc(stack, capacity * sizeof(Vec2));
				}

				stack[cp++] = neighbors[i];
			}
		}
	}

	free(stack);
}

/**
 * @brief Callback de clique do balde de tinta: dispara o flood fill na posição clicada.
 *
 * Converte as coordenadas float do mouse para inteiros (truncamento) e
 * delega ao @c flood_fill com a cor atualmente selecionada na paleta.
 *
 * @return Nenhum.
 */
void bucket_on_click()
{
	int x = app.art_curr.x;
	int y = app.art_curr.y;

	flood_fill(x, y, app.color);
}

/**
 * @brief Despachador genérico de clique: chama o callback da ferramenta se ele existir.
 *
 * Encapsula a verificação @c if(tool && tool->on_click) em um único
 * local, mantendo o laço principal limpo e tornando seguro adicionar
 * ferramentas que não implementam todos os eventos.
 *
 * @param tool Ferramenta-alvo (pode ser @c NULL).
 * @return Nenhum.
 */
void on_click(Tool *tool)
{
	if (tool && tool->on_click) {
		tool->on_click();
	}
}

/**
 * @brief Despachador genérico do evento de arrasto (motion).
 * @param tool Ferramenta-alvo.
 * @return Nenhum.
 */
void on_motion(Tool *tool)
{
	if (tool && tool->on_motion) {
		tool->on_motion();
	}
}

/**
 * @brief Despachador genérico do evento de liberação do botão (release).
 * @param tool Ferramenta-alvo.
 * @return Nenhum.
 */
void on_release(Tool *tool)
{
	if (tool && tool->on_release) {
		tool->on_release();
	}
}
