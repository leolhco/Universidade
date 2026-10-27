/**
 * @file toolbar.c
 * @brief Implementação da camada de interface gráfica (UI) do Mini Paint.
 *
 * Responsável por (a) calcular o LAYOUT dos componentes a partir das
 * dimensões da janela, (b) DESENHAR cada componente usando exclusivamente
 * as primitivas próprias do projeto (draw_fill_rect, draw_fill_circle,
 * put_string_in_rect) e (c) executar HIT-TESTING — converter um clique
 * em (x, y) na ação correspondente da UI (selecionar ferramenta,
 * trocar cor, mudar espessura, limpar canvas, salvar BMP).
 *
 * **Por que toda a UI é desenhada com primitivas próprias?** O enunciado
 * do Trabalho 1 exige que NÃO sejam usadas funções de desenho prontas;
 * essa exigência se aplica à UI tanto quanto à arte do usuário. Aqui,
 * cada botão é um retângulo preenchido por dois triângulos via scanline
 * fill (draw_fill_rect), cada bolinha do seletor de espessura é um disco
 * preenchido pelo algoritmo do ponto médio (draw_fill_circle) e cada
 * letra dos botões "NEW"/"SAVE" é um glifo 8x8 rasterizado bit a bit
 * (put_string_in_rect).
 *
 * **Estrutura do layout:**
 *
 *  +-----+------------------------------------------+
 *  |TOOL |                                          |
 *  |BAR  |                                          |
 *  |LEFT |              ÁREA DE ARTE                |
 *  |     |                                          |
 *  |     |                                          |
 *  +-----+------------------------------------------+
 *  |  PALETTE  |  THICKNESS  | NEW   |   SAVE       |
 *  +-----------+-------------+-------+--------------+
 */

#include "paint.h"
#include "canvas.h"
#include "shapes.h"
#include "color.h"
#include "tools.h"
#include "text.h"

#include <stddef.h>

/**
 * @brief Cor de destaque usada para indicar o item atualmente selecionado
 *        (ferramenta, cor da paleta ou espessura).
 */
#define SELECTED ROYALBLUE 

/** @brief Número de cores da paleta — atende o requisito mínimo do enunciado ("pelo menos 8 cores"). */
#define NUM_COLORS 8

/** @brief Número de níveis de espessura — atende ao requisito do enunciado ("3 opções: fino, médio, grosso"). */
#define NUM_THICKNESS 3

/**
 * @brief Paleta de cores: agrega o retângulo total, os retângulos de cada botão e as cores em si.
 */
struct palette {
	Rect rect;                  /**< Retângulo total ocupado pela paleta na tela (usado em hit_palette). */
	Rect bounds[NUM_COLORS];    /**< Retângulo de cada botão de cor (hit-testing individual). */
	uint32_t colors[NUM_COLORS];/**< Cores RGBA disponíveis. */
};
typedef struct palette Palette;

/** @brief Instância única da paleta. */
Palette palette;

/**
 * @brief Vetor com as 8 cores pré-definidas da paleta.
 *
 * Conforme exigido pelo enunciado: "preto, branco, vermelho, verde,
 * azul, amarelo, ciano, magenta".
 */
uint32_t palette_colors[NUM_COLORS] = {
	BLACK, WHITE, RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA
};

/**
 * @brief Seletor de espessura: análogo à paleta, mas para os três níveis (THIN/MEDIUM/THICK).
 */
struct thickness {
	Rect rect;                       /**< Retângulo total do seletor. */
	Rect bounds[NUM_THICKNESS];      /**< Botão de cada nível. */
	int nivel[NUM_THICKNESS];        /**< Valores numéricos dos níveis (em pixels). */
};
typedef struct thickness Thickness;

/** @brief Instância única do seletor de espessura. */
Thickness thickness;

/**
 * @brief Botão genérico (apenas um retângulo de bounds).
 */
struct button {
	Rect bounds; /**< Retângulo do botão na tela. */
};
typedef struct button Button;

/** @brief Botão "NEW" (limpa o canvas). */
Button new;
/** @brief Botão "SAVE" (exporta o canvas como BMP). */
Button save;

/** @brief Retângulo total da toolbar lateral (esquerda). */
Rect toolbar_l;
/** @brief Retângulo total da toolbar inferior. */
Rect toolbar_b;

/* === Coordenadas absolutas de cada componente de UI (calculadas em init_ui_components) === */

int toolbar_l_x; /**< X da toolbar esquerda. */
int toolbar_l_y; /**< Y da toolbar esquerda. */
int toolbar_l_w; /**< Largura da toolbar esquerda. */
int toolbar_l_h; /**< Altura da toolbar esquerda. */

int toolbar_b_x; /**< X da toolbar inferior. */
int toolbar_b_y; /**< Y da toolbar inferior. */
int toolbar_b_w; /**< Largura da toolbar inferior. */
int toolbar_b_h; /**< Altura da toolbar inferior. */

int palette_x; /**< X da paleta de cores. */
int palette_y; /**< Y da paleta de cores. */
int palette_w; /**< Largura da paleta. */
int palette_h; /**< Altura da paleta. */

int thickness_x; /**< X do seletor de espessura. */
int thickness_y; /**< Y do seletor de espessura. */
int thickness_w; /**< Largura do seletor. */
int thickness_h; /**< Altura do seletor. */

int new_x; /**< X do botão NEW. */
int new_y; /**< Y do botão NEW. */
int new_w; /**< Largura do botão NEW. */
int new_h; /**< Altura do botão NEW. */

int save_x; /**< X do botão SAVE. */
int save_y; /**< Y do botão SAVE. */
int save_w; /**< Largura do botão SAVE. */
int save_h; /**< Altura do botão SAVE. */

/**
 * @brief Calcula o layout completo da UI a partir das dimensões da janela.
 *
 * Todas as posições são expressas como FRAÇÕES de @c app.window_width e
 * @c app.window_height (ex.: a toolbar lateral ocupa 7.5% da largura e
 * 8/9 da altura). Isso torna o layout escalável: basta alterar
 * WINDOW_WIDTH/WINDOW_HEIGHT em paint.c e tudo se reorganiza
 * automaticamente.
 *
 * Após calcular as caixas de cada componente, a função também define:
 *  - @c app.art_width  = largura da janela menos a toolbar lateral;
 *  - @c app.art_height = altura da janela menos a toolbar inferior;
 *  - @c app.art_offset = (x, y) do canto superior-esquerdo do canvas
 *    de arte dentro da tela — é o vetor usado na conversão
 *    coordenadas-de-tela → coordenadas-de-arte realizada no laço
 *    principal (paint.c).
 *
 * @return Nenhum.
 *
 * @note Deve ser chamada UMA ÚNICA VEZ antes de qualquer outra função
 *       deste módulo e antes da alocação dos buffers de pixels.
 */
void init_ui_components()
{
	int window_width = app.window_width;
	int window_height = app.window_height;

	toolbar_l_x = 0;
	toolbar_l_y = 0;
	toolbar_l_w = window_width * 0.075f;
	toolbar_l_h = window_height * 8.0f / 9.0f;

	toolbar_b_x = 0;
	toolbar_b_y = toolbar_l_h;
	toolbar_b_w = window_width;
	toolbar_b_h = window_height - toolbar_l_h;

	palette_x = toolbar_b_x;
	palette_y = toolbar_b_y;
	palette_w = toolbar_b_w * 0.5f;
	palette_h = toolbar_b_h;

	thickness_x = palette_x + palette_w;
	thickness_y = toolbar_b_y;
	thickness_w = (toolbar_b_w - palette_w) * 0.5f;
	thickness_h = toolbar_b_h;

	new_x = thickness_x + thickness_w;
	new_y = toolbar_b_y;
	new_w = (toolbar_b_w - palette_w - thickness_w) * 0.5f;
	new_h = toolbar_b_h;

	save_x = new_x + new_w;
	save_y = toolbar_b_y;
	save_w = (toolbar_b_w - palette_w - thickness_w) * 0.5f;
	save_h = toolbar_b_h;

	toolbar_l = (Rect){
		{ toolbar_l_x, toolbar_l_y },
		{ toolbar_l_w, toolbar_l_h }
	};

	toolbar_b = (Rect){
		{ toolbar_b_x, toolbar_b_y },
		{ toolbar_b_w, toolbar_b_h }
	};

	palette.rect = (Rect){
		{ palette_x, palette_y },
		{ palette_w, palette_h }
	};

	thickness.rect = (Rect){
		{ thickness_x, thickness_y },
		{ thickness_w, thickness_h }
	};

	new.bounds = (Rect){
		{ new_x, new_y },
		{ new_w, new_h }
	};

	save.bounds = (Rect){
		{ save_x, save_y },
		{ save_w, save_h }
	};

	thickness.nivel[0] = THIN;
	thickness.nivel[1] = MEDIUM;
	thickness.nivel[2] = THICK;

	for (int i = 0; i < NUM_COLORS; i++) {
		palette.colors[i] = palette_colors[i];
	}

	app.art_width = app.window_width - toolbar_l.size.x;
	app.art_height = app.window_height - toolbar_b.size.y;
	app.art_offset = (Vec2){ toolbar_l.size.x, 0 };
}

/**
 * @brief Desenha a toolbar lateral com os 8 botões de ferramenta.
 *
 * Divide a toolbar verticalmente em 8 células iguais. Cada célula é
 * pintada com a cor de destaque se for a ferramenta selecionada, ou com
 * cinza caso contrário. Em seguida o ícone da ferramenta é renderizado
 * via @c tools[i]->draw_icon — outro exemplo de polimorfismo, em que a
 * toolbar não precisa "saber" como cada ferramenta é desenhada.
 *
 * Também atualiza @c tools[i]->bounds com a caixa real do botão na tela,
 * para que hit_toolbar_left() possa testá-la depois.
 *
 * @return Nenhum.
 */
void draw_toolbar_left(void)
{
	draw_fill_rect(app.screen, &toolbar_l, DIMGREY);

	float x = toolbar_l.pos.x;
	float y = toolbar_l.pos.y;
	float w = toolbar_l.size.x;
	float h = toolbar_l.size.y;

	float cell = h / 8.0f;

	float mx = 0.05f * w; 
	float my = 0.05f * cell;

	for (int i = 0; i < NUM_TOOLS; i++) {
		Rect btn = {
			.pos = { x + mx, y + my + cell * i },
			.size = { w - mx - mx, cell - my - my }
		};

		draw_fill_rect(app.screen, &btn, (app.tool == tools[i]) ? SELECTED : GREY);
		tools[i]->draw_icon(&btn);
		tools[i]->bounds = btn;
	}
}

/**
 * @brief Desenha a paleta de cores com NUM_COLORS botões em fileira.
 *
 * Cada botão é um retângulo cinza (ou azul se selecionado) com uma
 * amostra da cor centralizada — fornecendo o feedback visual exigido
 * pelo critério "Interface usável e responsiva".
 *
 * @return Nenhum.
 */
void draw_palette(void)
{
	draw_fill_rect(app.screen, &palette.rect, DIMGREY);

	float x = palette.rect.pos.x;
	float y = palette.rect.pos.y;
	float w = palette.rect.size.x;
	float h = palette.rect.size.y;

	float cell = w / NUM_COLORS;

	float mx = 0.1f * cell; 
	float my = 0.1f * h;

	for (int i = 0; i < NUM_COLORS; i++) {
		Rect btn = {
			{ x + mx + cell * i, y + my },
			{ cell - mx - mx, h - my - my }
		};

		draw_fill_rect(app.screen, &btn, (app.color == palette.colors[i]) ? SELECTED : GREY);

		Rect color = {
			{ btn.pos.x + mx, btn.pos.y + my },
			{ btn.size.x - mx - mx, btn.size.y - my - my }
		};

		draw_fill_rect(app.screen, &color, palette.colors[i]);

		palette.bounds[i] = btn;
	}
}

/**
 * @brief Desenha o seletor de espessura (3 botões com "halteres" de tamanhos crescentes).
 *
 * Cada botão exibe um "haltere" — dois círculos preenchidos conectados
 * por um retângulo — cujo raio cresce linearmente com o índice @c i,
 * dando feedback visual imediato sobre qual espessura está sendo
 * escolhida (atende ao item "feedback visual" do critério de UI).
 *
 * @return Nenhum.
 */
void draw_thickness_option(void)
{
	draw_fill_rect(app.screen, &thickness.rect, DIMGREY);

	float x = thickness.rect.pos.x;
	float y = thickness.rect.pos.y;
	float w = thickness.rect.size.x;
	float h = thickness.rect.size.y;

	float cell = w / NUM_THICKNESS;

	float mx = 0.1f * cell; 
	float my = 0.1f * h;

	for (int i = 0; i < NUM_THICKNESS; i++) {
		Rect btn = {
			{ x + mx + cell * i, y + my },
			{ cell - mx - mx, h - my - my }
		};

		draw_fill_rect(app.screen, &btn, (app.thickness == thickness.nivel[i]) ? SELECTED : GREY);

		float mxt = btn.size.x * 0.1f;

		int r = 0.025f * (i + 1) * btn.size.x;
		Vec2 center1 = { btn.pos.x + r + mxt, btn.pos.y + btn.size.y * 0.5f };
		Vec2 center2 = { btn.pos.x + btn.size.x - r - mxt, btn.pos.y + btn.size.y * 0.5f };

		Circle circle1 = { center1, r };
		Circle circle2 = { center2, r };

		draw_fill_circle(app.screen, &circle1, BLACK);
		draw_fill_circle(app.screen, &circle2, BLACK);

		Rect opt = {
			{ center1.x, center1.y - r },
			{ center2.x - center1.x, 2 * r + 1 }
		};

		draw_fill_rect(app.screen, &opt, BLACK);

		thickness.bounds[i] = btn;
	}
}

/**
 * @brief Desenha o botão "NEW" (limpar canvas).
 *
 * O texto "NEW" é rasterizado pela rotina put_string_in_rect (ver
 * text.c), que percorre os bits do glifo 8x8 e desenha cada bit aceso
 * como um retângulo preenchido — escalado pelo fator @c scale para que
 * fique legível.
 *
 * @return Nenhum.
 */
void draw_new_button(void)
{
	Rect new = { { new_x, new_y }, { new_w, new_h } };

	float x = new.pos.x;
	float y = new.pos.y;
	float w = new.size.x;
	float h = new.size.y;

	float mx = 0.1f * w;
	float my = 0.1f * h;

	Rect btn = {
		{ x + mx, y + my },
		{ w - mx - mx, h - my - my }
	};

	Rect opt = {
		{ btn.pos.x + 0.1f * btn.size.x, btn.pos.y + 0.1f * btn.size.y },
		{ btn.size.x - 2.0f * 0.1f * btn.size.x, btn.size.y - 2.0f * 0.1f * btn.size.y }
	};

	draw_fill_rect(app.screen, &btn, GREY);
	draw_fill_rect(app.screen, &opt, LIGHTGREY);

	int scale = 2;
	int space = 1;

	put_string_in_rect(
			app.screen,
			&opt,
			"NEW",
			scale,
			space,
			BLACK
			);
}

/**
 * @brief Desenha o botão "SAVE" (exportar canvas como BMP).
 * @return Nenhum.
 */
void draw_save_button(void)
{
	Rect new = { { save_x, save_y}, { save_w, save_h } };

	float x = new.pos.x;
	float y = new.pos.y;
	float w = new.size.x;
	float h = new.size.y;

	float mx = 0.1f * w;
	float my = 0.1f * h;

	Rect btn = {
		{ x + mx, y + my },
		{ w - mx - mx, h - my - my }
	};

	Rect opt = {
		{ btn.pos.x + 0.1f * btn.size.x, btn.pos.y + 0.1f * btn.size.y },
		{ btn.size.x - 2.0f * 0.1f * btn.size.x, btn.size.y - 2.0f * 0.1f * btn.size.y }
	};

	draw_fill_rect(app.screen, &btn, GREY);
	draw_fill_rect(app.screen, &opt, LIGHTGREY);

	int scale = 2;
	int space = 1;

	put_string_in_rect(
			app.screen,
			&opt,
			"SAVE",
			scale,
			space,
			BLACK
			);
}

/**
 * @brief Redesenha a toolbar inferior por completo (paleta + espessura + botões).
 *
 * Chamada apenas quando o conteúdo da barra inferior muda (troca de cor
 * ou de espessura), em vez de a cada frame — otimização padrão de UI
 * imediata.
 *
 * @return Nenhum.
 */
void draw_toolbar_bottom(void)
{
	draw_fill_rect(app.screen, &toolbar_b, DIMGREY);
	draw_palette();
	draw_thickness_option();
	draw_new_button();
	draw_save_button();
}

/**
 * @brief Hit-test da toolbar lateral.
 *
 * Estratégia em duas fases (otimização clássica de hit-testing):
 *  1. Rejeição rápida: se o cursor não está no retângulo da toolbar
 *     inteira, retorna @c NULL sem testar os 8 botões individualmente.
 *  2. Teste individual: percorre as 8 ferramentas e retorna a primeira
 *     cujo @c bounds contém o cursor.
 *
 * @return Ferramenta clicada, ou @c NULL se nenhuma.
 */
Tool *hit_toolbar_left()
{
	if (!point_in_rect(&app.screen_curr, &toolbar_l)) return NULL;

	for (int i = 0; i < NUM_TOOLS; i++) {
		if (point_in_rect(&app.screen_curr, &tools[i]->bounds)) {
			return tools[i];
		}
	}

	return NULL;
}

/**
 * @brief Hit-test da paleta de cores. Mesma estratégia em duas fases do hit_toolbar_left.
 *
 * @return Ponteiro para a cor clicada, ou @c NULL.
 * @note Retornar ponteiro (em vez do valor) permite que o chamador
 *       distinga "cor preta foi clicada" (não-nulo apontando para 0) de
 *       "nenhuma cor foi clicada" (NULL).
 */
uint32_t *hit_palette()
{
	if (!point_in_rect(&app.screen_curr, &palette.rect)) {
		return NULL;
	}

	for (int i = 0; i < NUM_COLORS; i++) {
		if (point_in_rect(&app.screen_curr, &palette.bounds[i])) {
			return &palette.colors[i];
		}
	}

	return NULL;
}

/**
 * @brief Verifica se o cursor está dentro da área de desenho (canvas).
 *
 * Função crítica para o laço de eventos: distingue cliques no canvas
 * (que iniciam um traço) de cliques na toolbar (que são ações de UI).
 * O retângulo é montado on-the-fly a cada chamada usando o offset e as
 * dimensões da arte.
 *
 * @return @c true se o cursor está sobre o canvas; @c false caso contrário.
 */
bool hit_art_area()
{
	Rect area = {
		{ app.art_offset.x, app.art_offset.y },
		{ app.art->width, app.art->height }
	};

	return point_in_rect(&app.screen_curr, &area);
}

/**
 * @brief Hit-test do seletor de espessura.
 * @return Ponteiro para o nível clicado (1, 5 ou 15), ou @c NULL.
 */
int *hit_thickness()
{
	if (!point_in_rect(&app.screen_curr, &thickness.rect)) {
		return NULL;
	}

	for (int i = 0; i < NUM_THICKNESS; i++) {
		if (point_in_rect(&app.screen_curr, &thickness.bounds[i])) {
			return &thickness.nivel[i];
		}
	}

	return NULL;
}

/**
 * @brief Hit-test do botão NEW.
 * @return @c true se o botão NEW foi clicado.
 */
bool hit_new_button()
{
	return point_in_rect(&app.screen_curr, &new.bounds);
}

/**
 * @brief Hit-test do botão SAVE.
 * @return @c true se o botão SAVE foi clicado.
 */
bool hit_save_button()
{
	return point_in_rect(&app.screen_curr, &save.bounds);
}
