/**
 * @file game.h
 * @brief Interface do agregado da partida: jogador, inimigos e limites do mundo.
 *
 * Reune o estado do jogo (o tanque do jogador, o vetor de @c ENEMY_N
 * inimigos e o retangulo do mundo) e as funcoes que conduzem a partida:
 * inicializacao, atualizacao logica, colisoes, render e consultas de
 * fim de jogo / placar.
 */

#ifndef GAME_H
#define GAME_H

#include "tank.h"
#include "enemy.h"
#include "shapes.h"
#include "canvas.h"

/** @brief Numero de tanques inimigos na partida (e total a abater para vencer). */
#define ENEMY_N 10

/**
 * @brief Estado completo de uma partida.
 */
struct game {
	Tank player;  /**< Tanque controlado pelo jogador. */
	Enemy enemies[ENEMY_N];  /**< Vetor de tanques inimigos. */
	Rect bounds;  /**< Retangulo do mundo (limites da tela). */
};
typedef struct game Game;

/**
 * @brief Inicializa a partida: cria o jogador no centro e os inimigos nas bordas.
 * @param g      Jogo a inicializar.
 * @param width  Largura do mundo (tela).
 * @param height Altura do mundo (tela).
 * @return Nenhum.
 */
void game_init(Game *g, int width, int height);
/**
 * @brief Atualiza a logica de todos os tanques (jogador e inimigos) em um quadro.
 * @param g     Jogo.
 * @param move  Comando de avanco do jogador.
 * @param turn  Comando de giro do jogador.
 * @param mouse Mira do jogador (cursor), em mundo.
 * @param shot  Disparo do jogador.
 * @return Nenhum.
 */
void game_update(Game *g, float move, float turn, Vec2 *mouse, bool shot);
/**
 * @brief Resolve todas as colisoes do quadro (tiros que acertam e tanques que se sobrepoem).
 * @param g Jogo.
 * @return Nenhum.
 */
void game_collision(Game *g);
/**
 * @brief Desenha jogador e inimigos no canvas.
 * @param c Canvas de destino.
 * @param g Jogo.
 * @return Nenhum.
 */
void game_render(Canvas *c, Game *g);
/**
 * @brief Indica derrota (jogador morto).
 * @return @c true se o tanque do jogador esta @c DEAD.
 */
bool game_over(Game *g);
/**
 * @brief Indica vitoria (nenhum inimigo ativo restante).
 * @return @c true se todos os inimigos foram abatidos.
 */
bool game_won(Game *g);
/**
 * @brief Conta quantos inimigos ja foram abatidos (placar).
 * @return Numero de inimigos em estado @c DEAD.
 */
int game_kills(Game *g);

#endif

