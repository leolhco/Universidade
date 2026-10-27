/**
 * @file enemy.h
 * @brief Interface do inimigo: um tanque acrescido de estado de IA.
 *
 * O inimigo COMPOE um @c Tank (relacao "e-um-tanque" por composicao) e
 * adiciona o que a IA precisa: um contador de recarga de tiro
 * (@c cooldown / @c reset) e a distancia de parada (@c stop_distance), na
 * qual deixa de avancar para manter um vao ate o jogador.
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "tank.h"

/**
 * @brief Inimigo: tanque + estado de inteligencia artificial.
 */
struct enemy {
	Tank tank;  /**< Tanque do inimigo (composicao: geometria, cinematica e combate). */
	int cooldown;  /**< Contador regressivo (em quadros) ate o proximo tiro. */
	int reset;  /**< Valor de recarga: @c cooldown volta a ele apos disparar. */
	float stop_distance;  /**< Distancia ao jogador em que o inimigo para de avancar. */
};
typedef struct enemy Enemy;

/**
 * @brief Construtor do inimigo (inicializa o tanque interno e os parametros de IA).
 *
 * Repassa os parametros de tanque para @c _tank_ e configura a IA:
 * @c cooldown inicial, seu valor de recarga (@c reset) e a
 * @c stop_distance.
 *
 * @param e             Inimigo a inicializar.
 * @param center        Posicao de spawn no mundo.
 * @param size          Dimensoes base do casco.
 * @param vel           Velocidade linear.
 * @param angular       Incremento angular do casco (rad).
 * @param turret_speed  Giro maximo da torre por quadro (rad).
 * @param chassi_color  Cor do casco.
 * @param belt_color    Cor das esteiras.
 * @param hatch_color   Cor da escotilha.
 * @param turret_color  Cor da torre/canhao.
 * @param bounds        Limites do mundo.
 * @param speed         Velocidade do projetil.
 * @param damage        Dano do projetil.
 * @param proj_color    Cor do projetil.
 * @param health        Vida inicial.
 * @param cooldown      Recarga entre tiros, em quadros (valor inicial e de reset).
 * @param stop_distance Distancia ao jogador em que o inimigo para de avancar.
 * @return Nenhum.
 */
void _enemy_(
	Enemy *e,	
	Vec2 *center,
	Vec2 *size,
	float vel, 
	float angular,
	float turret_speed,
	uint32_t chassi_color,
	uint32_t belt_color,
	uint32_t hatch_color,
	uint32_t turret_color,

	Rect *bounds,
	float speed,
	int damage,
	uint32_t proj_color,

	int health,
	int cooldown,

	float stop_distance
	  );

/**
 * @brief Calcula os comandos da IA (girar, avancar, atirar) para perseguir o jogador.
 * @param e      Inimigo.
 * @param player Tanque do jogador (alvo).
 * @param move   Saida: comando de avanco.
 * @param turn   Saida: comando de giro.
 * @param shot   Saida: disparar neste quadro.
 * @return Nenhum.
 */
void enemy_ai(Enemy *e, Tank *player, float *move, float *turn, bool *shot);

/**
 * @brief Roda a IA e atualiza o tanque do inimigo (apenas se ele estiver @c ACTIVE).
 * @param e      Inimigo.
 * @param player Tanque do jogador (alvo da mira e da perseguicao).
 * @return Nenhum.
 */
void enemy_update(Enemy *e, Tank *player);

/**
 * @brief Desenha o inimigo se ele estiver @c ACTIVE.
 * @param c Canvas de destino.
 * @param e Inimigo.
 * @return Nenhum.
 */
void enemy_render(Canvas *c, Enemy *e);

#endif

