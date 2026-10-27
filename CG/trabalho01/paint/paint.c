/**
 * @file paint.c
 * @brief Ponto de entrada do Mini Paint: bootstrap, laço de eventos e composição da janela.
 *
 * Responsabilidades deste módulo:
 *
 * 1. **Inicialização da SDL e do framebuffer manual.** A SDL é usada
 *    estritamente para (a) criar a janela, (b) expor as @c SDL_Surface
 *    construídas SOBRE os nossos buffers de pixels (via
 *    SDL_CreateRGBSurfaceFrom) e (c) fazer o blit final dessa surface
 *    para a janela. Conforme exigido pelo enunciado do Trabalho 1,
 *    NENHUMA primitiva de desenho da SDL é usada — toda a cor escrita
 *    nos pixels passa pelas rotinas próprias do projeto.
 *
 * 2. **Laço principal de eventos** (event loop): polling de eventos do
 *    mouse, conversão de coordenadas tela→arte, despacho para os
 *    callbacks da ferramenta ativa (on_click/on_motion/on_release) e
 *    hit-testing dos componentes de UI clicados.
 *
 * 3. **Sistema de preview** para ferramentas de arrasto (linha,
 *    retângulo, círculo): a cada movimento do mouse, o canvas de arte é
 *    RESTAURADO a partir do @c buffer (snapshot tirado no clique
 *    inicial) ANTES de desenhar a nova forma — isso evita o
 *    "rastro" que apareceria se o desenho se acumulasse a cada quadro.
 *
 * @note SDL_BlitSurface, SDL_CreateRGBSurfaceFrom, SDL_GetWindowSurface,
 *       SDL_UpdateWindowSurface, SDL_PollEvent e SDL_GetMouseState NÃO
 *       são funções de desenho: são funções de janela/superfície/eventos,
 *       permitidas pelo enunciado.
 */

#include <SDL2/SDL.h>
#include "paint.h"
#include "canvas.h"
#include "shapes.h"
#include "color.h"
#include "toolbar.h"

/** @brief Título exibido na barra da janela. */
#define WINDOW_TITLE "Paint"
/** @brief Largura da janela, em pixels. */
#define WINDOW_WIDTH 1280
/** @brief Altura da janela, em pixels. */
#define WINDOW_HEIGHT 720

/** @brief Framebuffer da janela inteira (tela + arte composta). */
Canvas screen;
/** @brief Framebuffer da área de desenho do usuário (o canvas exportado). */
Canvas art;
/** @brief Snapshot da arte usado para o sistema de preview de formas. */
Canvas buffer;
/** @brief Ponteiro para a janela criada pela SDL. */
SDL_Window *window = NULL;
/** @brief Surface da janela (destino final do blit). */
SDL_Surface *window_surface = NULL;
/** @brief Surface SDL que aponta diretamente para os pixels de @c screen. */
SDL_Surface *screen_surface = NULL;
/** @brief Surface SDL que aponta para os pixels de @c art (usada por SDL_SaveBMP). */
SDL_Surface *art_surface = NULL;

/**
 * @brief Instância global única do estado da aplicação (declarada em paint.h).
 */
App app;

/**
 * @brief Compõe o frame final da janela e o entrega à SDL para exibição.
 *
 * Sequência:
 * 1. Faz o BLIT (cópia de bloco, ver canvas.c) da arte sobre o canvas da
 *    tela na posição @c art_offset — esse é o passo de COMPOSIÇÃO: a
 *    arte vive em seu próprio framebuffer e é "colada" sobre a tela a
 *    cada quadro, sem precisar redesenhar a toolbar.
 * 2. SDL_BlitSurface copia os pixels da nossa surface para a surface da
 *    janela.
 * 3. SDL_UpdateWindowSurface entrega o quadro ao gerenciador de janelas.
 *
 * @return Nenhum.
 *
 * @note A toolbar é desenhada apenas quando muda (mudança de ferramenta,
 *       cor ou espessura), enquanto a arte é blitada a cada quadro. Isso
 *       reduz o custo de redesenho — só o que mudou é rasterizado.
 */
void update_window(void)
{
	canvas_blit(
			app.screen,
			app.art_offset.x,
			app.art_offset.y,
			app.art,
			0,
			0,
			app.art->width,
			app.art->height
		  );

	SDL_BlitSurface(screen_surface, NULL, window_surface, NULL);
	SDL_UpdateWindowSurface(window);
}

/**
 * @brief Limpa a área de desenho preenchendo-a totalmente de branco.
 *
 * Implementa o botão "NEW" exigido pelo enunciado: "limpar canvas com
 * cor de fundo".
 *
 * @return Nenhum.
 */
void new_canvas()
{
	canvas_fill(app.art, WHITE);
}

/**
 * @brief Exporta a área de desenho como arquivo BMP ("output.bmp").
 *
 * Implementa o botão "SAVE" exigido pelo enunciado. A SDL é usada APENAS
 * para a serialização do formato BMP (SDL_SaveBMP); os pixels gravados
 * são exatamente os mesmos do nosso framebuffer manual, pois
 * @c art_surface foi construída SOBRE @c art.pixels.
 *
 * @return Nenhum.
 *
 * @warning Sobrescreve "output.bmp" no diretório de trabalho a cada chamada.
 */
void save_bmp()
{
	SDL_SaveBMP(art_surface, "output.bmp");
}

/**
 * @brief Função principal: monta os recursos, entra no laço de eventos e libera tudo na saída.
 *
 * Estrutura de alto nível:
 *
 *  1. Preenche os campos iniciais de @c app (dimensões, ferramenta
 *     padrão, cor padrão, espessura padrão).
 *  2. Chama init_ui_components() — calcula posições e dimensões da UI e
 *     define o tamanho do canvas de arte (@c art_width / @c art_height).
 *  3. Aloca os três buffers de pixels via @c malloc e os associa aos
 *     três Canvas via canvas_init().
 *  4. Inicializa a SDL, cria a janela e constrói duas @c SDL_Surface
 *     que apontam diretamente para os nossos buffers (parâmetros 0xFF000000,
 *     0x00FF0000, 0x0000FF00, 0x000000FF definem o layout RGBA empacotado
 *     em 32 bits — exatamente o formato definido em color.h).
 *  5. Pinta o estado inicial (tela branca, arte branca, toolbars).
 *  6. Entra no LAÇO DE EVENTOS (descrito a seguir).
 *  7. Libera todos os recursos na saída.
 *
 * **Laço de eventos (event loop)** — coração da interatividade exigida
 * pelo critério "Interface usável e responsiva":
 *
 * - SDL_PollEvent retira um evento da fila por iteração.
 * - SDL_GetMouseState obtém a posição atual do cursor.
 * - As coordenadas são convertidas para os dois sistemas:
 *   @c app.screen_curr (tela) e @c app.art_curr (canvas, subtraindo
 *   @c art_offset). @c app.*_prev guarda a posição anterior para que o
 *   pincel conecte movimentos consecutivos com segmentos contínuos
 *   (essencial para que o lápis não desenhe "pontilhado" em movimentos
 *   rápidos do mouse, em que SDL_MOUSEMOTION é amostrado em saltos).
 *
 * - Se o botão esquerdo está pressionado E o cursor está sobre a arte:
 *   - PRESSED → inicia o traço, salva @c art_start, tira SNAPSHOT do
 *     canvas no @c buffer (apenas para ferramentas com preview), e
 *     chama on_click.
 *   - MOTION durante drawing → para ferramentas com preview, RESTAURA a
 *     arte a partir do snapshot (apaga a forma anterior) antes de
 *     chamar on_motion (que desenha a nova forma); para ferramentas
 *     sem preview (lápis, borracha), apenas chama on_motion para
 *     estender o traço.
 *
 * - Se o botão foi liberado:
 *   - Se estava desenhando: finaliza o traço (restaura do snapshot e
 *     desenha a forma definitiva via on_release).
 *   - Se NÃO estava desenhando: testa hits nos componentes de UI
 *     (toolbar lateral, paleta, espessura, NEW, SAVE) e aplica a ação.
 *
 * - Após processar todos os eventos do quadro, redesenha as toolbars
 *   que foram marcadas como sujas e compõe a janela com update_window().
 *
 * @return 0 em saída normal.
 *
 * @note Não há controle explícito de FPS: o laço é direcionado a
 *       eventos (renderiza quando algo acontece), o que dá fluidez
 *       máxima ao desenho a mão livre.
 * @warning Não há tratamento de falha em @c malloc nem em SDL_Init —
 *          aceitável para um trabalho acadêmico, mas valeria a pena
 *          mencionar em uma versão de produção.
 */
int main(void)
{
	app.window_width = WINDOW_WIDTH;
	app.window_height = WINDOW_HEIGHT;
	app.screen = &screen;
	app.art = &art;
	app.buffer = &buffer;
	app.tool = tools[0];
	app.color = BLACK;
	app.thickness = THIN;

	init_ui_components();

	uint32_t *screen_pixels = malloc(WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t));
	uint32_t *art_pixels = malloc(app.art_width * app.art_height * sizeof(uint32_t));
	uint32_t *buffer_pixels = malloc(app.art_width * app.art_height * sizeof(uint32_t));

	canvas_init(&screen, screen_pixels, WINDOW_WIDTH, WINDOW_HEIGHT);
	canvas_init(&art, art_pixels, app.art_width, app.art_height);
	canvas_init(&buffer, buffer_pixels, app.art_width, app.art_height);

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN
			);

	window_surface = SDL_GetWindowSurface(window);

	screen_surface = SDL_CreateRGBSurfaceFrom(
			screen_pixels,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			32,
			WINDOW_WIDTH * 4,
			0xFF000000,
			0x00FF0000,
			0x0000FF00,
			0x000000FF
			);

	art_surface = SDL_CreateRGBSurfaceFrom(
			app.art->pixels,
			app.art->width,
			app.art->height,
			32,
			app.art->width * 4,
			0xFF000000,
			0x00FF0000,
			0x0000FF00,
			0x000000FF
			);

	canvas_fill(app.screen, WHITE);
	canvas_fill(app.art, WHITE);

	draw_toolbar_left();
	draw_toolbar_bottom();

	update_window();

	bool motion = false;
	bool pressed = false;
	bool released = false;
	bool drawing = false;
	bool update_toolbar_left = false;
	bool update_toolbar_bottom = false;

	Vec2 curr = { 0, 0 }, prev = { 0, 0 }, start = { 0, 0 };

	bool running = true;
	SDL_Event e;
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}

			int x, y;
			Uint32 flags = SDL_GetMouseState(&x, &y);
			bool left = flags & SDL_BUTTON_LMASK;

			Vec2 mouse = { x, y };
			prev = curr;
			curr = mouse;


			app.screen_prev = prev;
			app.screen_curr = curr;

			app.art_prev = (Vec2){ app.screen_prev.x - app.art_offset.x, app.screen_prev.y - app.art_offset.y };
			app.art_curr = (Vec2){ app.screen_curr.x - app.art_offset.x, app.screen_curr.y - app.art_offset.y };

			motion = false;
			pressed = false;
			released = false;

			switch (e.type) {
				case SDL_MOUSEMOTION:
					motion = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					pressed = true;
					break;
				case SDL_MOUSEBUTTONUP:
					released = true;
					break;
				default: break;
			}

			if (left) {
				if (hit_art_area()) {
					if (pressed) {
						if (e.button.button != SDL_BUTTON_LEFT) continue;

						drawing = true;

						start = curr;
						app.screen_start = start;
						app.art_start = (Vec2){ app.screen_start.x - app.art_offset.x, app.screen_start.y - app.art_offset.y };

						app.art_prev = app.art_curr;
						app.screen_prev = app.screen_curr;

						if (app.tool->preview) {
							canvas_blit(
									app.buffer,
									0,
									0,
									app.art,
									0,
									0,
									app.buffer->width,
									app.buffer->height
								   );
						}

						on_click(app.tool);
					} else if (motion && drawing) {
						if (app.tool->preview) {
							canvas_blit(
									app.art,
									0,
									0,
									app.buffer,
									0,
									0,
									app.art->width,
									app.art->height
								   );
						}

						on_motion(app.tool);
					}
				}
			}

			if (released) {
				Tool *tool;
				uint32_t *color;
				int *thick;

				if (e.button.button != SDL_BUTTON_LEFT) continue;

				if (drawing) {
					drawing = false;

					if (app.tool->preview) {
						canvas_blit(
								app.art,
								0,
								0,
								app.buffer,
								0,
								0,
								app.art->width,
								app.art->height
							   );
					}

					on_release(app.tool);
					continue;
				}

				tool = hit_toolbar_left();
				if (tool) {
					app.tool = tool;
					update_toolbar_left = true;
					continue;
				}

				color = hit_palette();
				if (color) {
					app.color = *color;
					update_toolbar_bottom = true;
					continue;
				}

				thick = hit_thickness();
				if (thick) {
					app.thickness = *thick;
					update_toolbar_bottom = true;
					continue;
				}

				if (hit_new_button()) {
					new_canvas();
					continue;
				}

				if (hit_save_button()) {
					save_bmp();
					continue;
				}
			}
		}

		if (update_toolbar_left) {
			draw_toolbar_left();
			update_toolbar_left = false;
		} else if (update_toolbar_bottom) {
			draw_toolbar_bottom();
			update_toolbar_bottom = false;
		}

		update_window();
	}

	SDL_DestroyWindow(window);
	SDL_FreeSurface(screen_surface);
	SDL_FreeSurface(art_surface);
	SDL_Quit();

	free(screen_pixels);
	free(art_pixels);
	free(buffer_pixels);

	return 0;
}
