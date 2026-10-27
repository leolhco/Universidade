/**
 * @file game.c
 * @brief Orquestracao da partida: criacao, atualizacao, matriz de colisoes, render e fim de jogo.
 *
 * Conecta os modulos: cria o jogador e @c ENEMY_N inimigos (com cores e
 * parametros proprios), avanca a logica de todos por quadro, resolve TODAS
 * as colisoes par a par e decide vitoria/derrota. Os inimigos nascem FORA
 * da tela, ao redor das bordas, e dirigem para dentro.
 */

#include "game.h"
#include "color.h"

/* === Paletas de cores dos tanques ===
 * Dois esquemas "camuflados": tons de verde-oliva para os inimigos e tons
 * de violeta/azul-ardosia para o jogador. Cada peca (casco, torre, canhao,
 * esteira) tem sua cor, com variantes mais escuras servindo de contorno. */
#define OLIVEGREEN      COLOR( 62,  82,  48, 255)  /* chassi */
#define DARKOLIVE       COLOR( 42,  58,  30, 255)  /* contorno chassi */
#define MOSSGREEN       COLOR( 70,  92,  52, 255)  /* torre */
#define FORESTSHADOW    COLOR( 50,  68,  36, 255)  /* contorno torre */
#define GUNMETALGREEN   COLOR( 50,  65,  38, 255)  /* canhao */
#define DEEPOLIVE       COLOR( 30,  42,  22, 255)  /* contorno canhao */
#define TRACKBROWN      COLOR( 35,  30,  25, 255)  /* esteira */
 
#define SLATEBLUE       COLOR( 72,  68, 110, 255)  /* chassi */
#define DARKVIOLET      COLOR( 50,  46,  82, 255)  /* contorno chassi */
#define LAVENDERGREY    COLOR( 84,  80, 128, 255)  /* torre */
#define DUSKPURPLE      COLOR( 60,  56,  96, 255)  /* contorno torre */
#define STEELVIOLET     COLOR( 60,  56,  95, 255)  /* canhao */
#define TRACKPLUM       COLOR( 30,  25,  35, 255)  /* esteira */

/**
 * @brief Monta a partida: limites do mundo, tanque do jogador e formacao de inimigos.
 *
 * O mundo e o retangulo da tela. O jogador nasce no centro, com cor violeta.
 * Os @c ENEMY_N inimigos sao posicionados FORA da tela (coordenadas
 * negativas ou alem da borda, no vetor @c enemy_pos) distribuidos em cima,
 * embaixo e nas laterais, de modo a entrarem em cena dirigindo. Os inimigos
 * recebem parametros reduzidos (metade da velocidade linear, angular e de
 * giro de torre do jogador), cooldown de tiro ESCALONADO (@c 120*i + 30)
 * para que nao disparem todos no mesmo quadro, e uma @c stop_distance
 * (= @c height*0.5) que os faz parar a certa distancia em vez de colidir
 * com o jogador.
 *
 * @param g      Jogo a inicializar.
 * @param width  Largura do mundo.
 * @param height Altura do mundo.
 * @return Nenhum.
 */
void game_init(Game *g, int width, int height)
{
	g->bounds = (Rect){ { 0, 0 }, { width, height } };

	Vec2 center = { width * 0.5f , height * 0.5f };
	Vec2 size = { width * 0.03f, height * 0.1f };
	float vel = 1.5f;
	float angular = M_PI / 90.0f;
	float turret_speed = M_PI / 180.f * 1.2f;

	float proj_speed = width / 180.0f;
	uint32_t proj_color = DARKVIOLET;

	_tank_(
	     &g->player,
	     &center,
	     &size,
	     vel,
	     angular,
	     turret_speed,

	     SLATEBLUE,
	     TRACKPLUM,
	     LAVENDERGREY,
	     STEELVIOLET,

	     &g->bounds,
	     proj_speed,
	     1,
	     proj_color,

	     15
	     );

	Vec2 enemy_pos[ENEMY_N] = {
		{ width * 0.25f, -100 },
		{ width * 0.50f, -100 },
		{ width * 0.75f, -100 },
		{ width * 0.25f, height + 100 },
		{ width * 0.50f, height + 100 },
		{ width * 0.75f, height + 100 },
		{ -100, height * 0.33f },      
		{ -100, height * 0.66f },
		{ width + 100, height * 0.33f }, 
		{ width + 100, height * 0.66f },
	};

	for (int i = 0; i < ENEMY_N; i++) {
		_enemy_(
			&g->enemies[i],
			&enemy_pos[i],
			&size, 
			vel * 0.5,
			angular * 0.5f,
			turret_speed * 0.5f,

			OLIVEGREEN,
			TRACKBROWN,
			MOSSGREEN,
			GUNMETALGREEN,

			&g->bounds,
			proj_speed,
			1,
			DARKOLIVE,

			3,
		       	120 * i + 30,
			height * 0.5f
			);
	}
}

/**
 * @brief Avanca a logica do jogador (com a entrada) e de cada inimigo (com sua IA).
 * @return Nenhum.
 */
void game_update(Game *g, float move, float turn, Vec2 *mouse, bool shot)
{
	tank_update(&g->player, move, turn, mouse, shot);

	for (int i = 0; i < ENEMY_N; i++) {
		enemy_update(g->enemies + i, &g->player);
	}
}

/**
 * @brief Resolve, par a par, todos os impactos de tiro e sobreposicoes entre tanques.
 *
 * Para cada inimigo ATIVO trata, em ordem:
 *  - tiro do jogador acertando o inimigo (consome o tiro, aplica dano e,
 *    se a vida zera, marca @c DEAD);
 *  - tiro do inimigo acertando o jogador (consome o tiro, aplica dano e,
 *    se a vida do jogador zera, marca @c DEAD);
 *  - sobreposicao jogador-inimigo (resolve_collision_tank);
 *  - contra os demais inimigos (laco interno @c j): tiro de um inimigo que
 *    atinge outro e consumido, e tanques inimigos sobrepostos sao separados.
 *
 * E uma verificacao O(n^2) entre tanques — adequada para @c ENEMY_N pequeno.
 *
 * @param g Jogo.
 * @return Nenhum.
 */
void game_collision(Game *g)
{
	for (int i = 0; i < ENEMY_N; i++) {
		if (g->enemies[i].tank.state != ACTIVE) continue;

		if (g->player.projectile.active &&
				check_collision_proj_tank(&g->player.projectile, &g->enemies[i].tank)) {
			g->player.projectile.active = false;
			g->enemies[i].tank.health -= g->player.projectile.damage;

			if (g->enemies[i].tank.health <= 0) {
				g->enemies[i].tank.state = DEAD;
			}
		}

		if (g->enemies[i].tank.projectile.active && 
				check_collision_proj_tank(&g->enemies[i].tank.projectile, &g->player)) {
			g->enemies[i].tank.projectile.active = false;
			g->player.health -= g->enemies[i].tank.projectile.damage;

			if (g->player.health <= 0) {
				g->player.state = DEAD;
			}
		}

		if (check_collision_tank(&g->player, &g->enemies[i].tank)) {
			resolve_collision_tank(&g->player, &g->enemies[i].tank);
		}

		for (int j = 0; j < ENEMY_N; j++) {
			if (i == j || g->enemies[j].tank.state != ACTIVE) continue;

			if (check_collision_proj_tank(&g->enemies[i].tank.projectile, &g->enemies[j].tank)) {
				g->enemies[i].tank.projectile.active = false;
			}

			if (check_collision_tank(&g->enemies[i].tank, &g->enemies[j].tank)) {
				resolve_collision_tank(&g->enemies[i].tank, &g->enemies[j].tank);
			}
		}
	}
}

/**
 * @brief Desenha o jogador e, em seguida, todos os inimigos.
 * @param c Canvas de destino.
 * @param g Jogo.
 * @return Nenhum.
 */
void game_render(Canvas *c, Game *g)
{
	tank_render(c, &g->player);

	for (int i = 0; i < ENEMY_N; i++) {
		enemy_render(c, g->enemies + i);
	}
}

/**
 * @brief Derrota: verdadeiro quando o tanque do jogador esta @c DEAD.
 * @return @c true se o jogador morreu.
 */
bool game_over(Game *g)
{
	return g->player.state == DEAD;
}

/**
 * @brief Vitoria: verdadeiro quando nenhum inimigo continua @c ACTIVE.
 * @return @c true se todos os inimigos foram abatidos.
 */
bool game_won(Game *g)
{
	for (int i = 0; i < ENEMY_N; i++) {
		if (g->enemies[i].tank.state == ACTIVE) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Conta inimigos em estado @c DEAD (placar exibido na HUD).
 * @return Numero de inimigos abatidos.
 */
int game_kills(Game *g)
{
	int kills = 0;
	for (int i = 0; i < ENEMY_N; i++) {
		if (g->enemies[i].tank.state == DEAD) {
			++kills;
		}
	}

	return kills;
}

