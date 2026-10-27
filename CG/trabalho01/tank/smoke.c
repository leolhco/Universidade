/**
 * @file smoke.c
 * @brief Ponto de entrada do jogo "Smoke": bootstrap da SDL, game loop e composicao da tela.
 *
 * Jogo 2D de tanques construido SEM engine pronta (Trabalho 2). A SDL e
 * usada estritamente para (a) criar a janela, (b) expor uma @c SDL_Surface
 * construida SOBRE o nosso framebuffer manual (via SDL_CreateRGBSurfaceFrom),
 * (c) entregar o quadro pronto (SDL_BlitSurface/SDL_UpdateWindowSurface) e
 * (d) ler teclado/mouse. NENHUMA primitiva de desenho da SDL e usada: toda
 * rasterizacao (poligonos, circulos, texto) passa pelas rotinas proprias do
 * projeto operando sobre o @c Canvas.
 *
 * Pilares deste modulo:
 *
 *  1. **Game loop com passo de tempo fixo.** A cada iteracao o laco so
 *     avanca a simulacao se ja se passaram >= 16 ms desde o ultimo tick
 *     (~60 Hz). Isso desacopla a velocidade do jogo da velocidade da CPU:
 *     em maquinas rapidas o tanque nao "voa", pois a fisica e atualizada
 *     numa taxa constante.
 *
 *  2. **Separacao explicita entre LOGICA e RENDERIZACAO.** Cada quadro
 *     executa, nesta ordem fixa: leitura de entrada -> game_update()
 *     (atualiza estado: posicoes, angulos, tiros) -> game_collision()
 *     (resolve acertos e sobreposicoes) -> game_render() (desenha). O
 *     estado nunca e alterado durante o desenho, atendendo ao criterio de
 *     organizacao update/render exigido pela disciplina.
 *
 *  3. **Maquina de estados da partida.** game_won()/game_over() decidem se
 *     a partida terminou; na tela final o jogo congela a simulacao, mostra
 *     a mensagem e aguarda a tecla R para reiniciar.
 *
 * @note SDL_BlitSurface, SDL_CreateRGBSurfaceFrom, SDL_GetWindowSurface,
 *       SDL_UpdateWindowSurface, SDL_PollEvent, SDL_GetKeyboardState e
 *       SDL_GetMouseState NAO sao funcoes de desenho: sao funcoes de
 *       janela/superficie/evento/entrada, permitidas pelo enunciado.
 */

#include <SDL2/SDL.h>
#include <math.h>
#include "canvas.h"
#include "shapes.h"
#include "transform.h"
#include "color.h"
#include "tank.h"
#include "enemy.h"
#include "game.h"
#include "text.h"

/** @brief Titulo exibido na barra da janela. */
#define WINDOW_TITLE "Smoke"
/** @brief Largura da janela e do framebuffer, em pixels. */
#define WINDOW_WIDTH 1280
/** @brief Altura da janela e do framebuffer, em pixels. */
#define WINDOW_HEIGHT 720 

/** @brief Framebuffer manual da janela inteira (matriz de pixels rasterizada a mao). */
Canvas canvas;
/** @brief Janela criada pela SDL. */
SDL_Window *window = NULL;
/** @brief Surface da janela (destino final do blit). */
SDL_Surface *window_surface = NULL;
/** @brief Surface SDL que aponta DIRETAMENTE para os pixels de @c canvas. */
SDL_Surface *surface = NULL;

/**
 * @brief Entrega o framebuffer ja desenhado para a janela.
 *
 * Copia os pixels da nossa surface (que compartilha memoria com @c canvas)
 * para a surface da janela e solicita a atualizacao da tela. E o unico
 * ponto em que o conteudo rasterizado a mao se torna visivel.
 *
 * @return Nenhum.
 */
void update_window(void)
{
	SDL_BlitSurface(surface, NULL, window_surface, NULL);
	SDL_UpdateWindowSurface(window);
}

/**
 * @brief Funcao principal: cria os recursos, roda o game loop e libera tudo na saida.
 *
 * Sequencia de inicializacao:
 *  1. Aloca o buffer de pixels e associa-o ao @c canvas (canvas_init).
 *  2. Inicializa a SDL, cria a janela e constroi uma @c SDL_Surface
 *     APONTANDO para @c pixels (as mascaras 0xFF000000/0x00FF0000/
 *     0x0000FF00/0x000000FF definem o layout RGBA de 32 bits usado em
 *     color.h). Assim, tudo que escrevemos no framebuffer aparece na
 *     surface sem copia intermediaria.
 *
 * **Game loop** (apos o rotulo @c again, que e tambem o ponto de
 * reinicio): a cada volta retira os eventos da fila (SDL_QUIT encerra),
 * aplica o passo de tempo fixo (descarta a iteracao se < 16 ms desde o
 * ultimo tick -> ~60 FPS) e le o estado do teclado/mouse.
 *
 *  - Se a partida terminou (vitoria ou derrota): desenha a mensagem
 *    central e "PRESS R TO RESTART"; ao pressionar R salta para @c again,
 *    reconstruindo o @c Game do zero.
 *  - Caso contrario: traduz as teclas em comandos (W/S -> avancar/recuar,
 *    A/D -> girar), le a posicao do mouse (mira da torre) e o botao
 *    esquerdo (disparo); entao executa, em ordem, game_update() ->
 *    game_collision() -> canvas_fill(BROWN) (limpa o fundo) ->
 *    game_render() -> HUD com o placar (abatidos / total). Por fim
 *    update_window() exibe o quadro.
 *
 * @return 0 em saida normal.
 *
 * @note O laco e de passo fixo (~60 Hz), e nao orientado a eventos: o
 *       estado avanca em incrementos de tempo constantes, o que mantem a
 *       fisica estavel independentemente do hardware.
 * @note O reinicio e feito com @c goto para o rotulo @c again, que
 *       re-declara e re-inicializa o @c Game na pilha.
 * @warning Nao ha tratamento de falha em @c malloc nem em SDL_Init —
 *          aceitavel para um trabalho academico.
 */
int main(void)
{
	uint32_t *pixels = malloc(WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t));

	canvas_init(&canvas, pixels, WINDOW_WIDTH, WINDOW_HEIGHT);

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

	surface = SDL_CreateRGBSurfaceFrom(
			pixels,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			32,
			WINDOW_WIDTH * 4,
			0xFF000000,
			0x00FF0000,
			0x0000FF00,
			0x000000FF
			);

	Game game;

	/* Rotulo de reinicio: o salto "goto again" (tecla R) recomeca a partida daqui. */
again:

	game_init(&game, WINDOW_WIDTH, WINDOW_HEIGHT);

	Uint64 last_tick = 0;

	bool running = true;
	SDL_Event e;
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}

		if (SDL_GetTicks() - last_tick < 16) continue;

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		bool won = game_won(&game);
		bool over = game_over(&game);
		bool finished = won || over;

		if (finished) {
			const char *msg = won ? "GAME WON" : "GAME OVER";

			Rect top = {
				{ 0, WINDOW_HEIGHT * 0.40f },
				{ WINDOW_WIDTH, 0 }
			};
			Rect bot = {
				{ 0, WINDOW_HEIGHT * 0.50f },
				{ WINDOW_WIDTH, 0 }
			};

			put_string_in_rect(&canvas, &top, msg, 6, 2, YELLOW); 
			put_string_in_rect(&canvas, &bot, "PRESS R TO RESTART", 3, 2, YELLOW); 

			update_window();

			if (currentKeyStates[SDL_SCANCODE_R]) {
				goto again;
			}

			continue;
		}

		float move = 0;
		float turn = 0;

		last_tick = SDL_GetTicks();

		if (currentKeyStates[SDL_SCANCODE_W]) { move++; }
		if (currentKeyStates[SDL_SCANCODE_S]) { move--; }
		if (currentKeyStates[SDL_SCANCODE_A]) { turn++; };
		if (currentKeyStates[SDL_SCANCODE_D]) { turn--; };

		int x, y;

		Uint32 mouse_state = SDL_GetMouseState(&x, &y);

		Vec2 mouse = { x, y };
		bool shot = mouse_state & SDL_BUTTON_LMASK;

		game_update(&game, move, turn, &mouse, shot);

		game_collision(&game);

		canvas_fill(&canvas, BROWN);

		game_render(&canvas, &game);

		char score[16];
		snprintf(score, sizeof(score), "%.2d / %.2d", game_kills(&game), ENEMY_N);

		Rect score_box = {
			{ WINDOW_WIDTH * 0.02f , 0 }, 
			{ WINDOW_WIDTH * 0.12f, WINDOW_HEIGHT * 0.07f }
		};

		put_string_in_rect(&canvas, &score_box, score, 2, 2, WHITE);

		update_window();
	}

	SDL_DestroyWindow(window);
	SDL_FreeSurface(surface);
	SDL_Quit();

	free(pixels);

	return 0;
}

