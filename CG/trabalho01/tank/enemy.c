/**
 * @file enemy.c
 * @brief Implementacao do inimigo: IA de perseguicao e tiro com recarga.
 *
 * A IA aponta o CASCO para o jogador (mesmo calculo de angulo por @c atan2
 * usado na mira do jogador), avanca apenas quando ja esta razoavelmente
 * alinhada e ainda longe (mantendo um vao), e atira em intervalos regulados
 * por um cooldown. A mira da TORRE e obtida reaproveitando @c tank_update:
 * passa-se a posicao do jogador no lugar do "mouse", de modo que a torre
 * rastreie o jogador automaticamente.
 */

#include "enemy.h"
#include <math.h>

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
	)
{
	_tank_(
		&e->tank,
		center,
		size,
		vel,
		angular,
		turret_speed,
		chassi_color,
		belt_color,
		hatch_color,
		turret_color,
		bounds,
		speed,
		damage,
		proj_color,

		health
	      );

	e->cooldown = cooldown;
	e->reset = cooldown;
	e->stop_distance = stop_distance;
}


/**
 * @brief Decide girar/avancar/atirar para caçar o jogador.
 *
 * Calcula o angulo-alvo do casco a partir do vetor (jogador - inimigo) com a
 * mesma convencao do resto do jogo (@c -atan2(dy,dx) - @c M_PI/2) e a
 * diferenca @c d para o angulo atual, normalizada para (-pi, pi]. O giro
 * (@c turn) e sempre no sentido de @c d (menor arco). So avanca
 * (@c move = 1) quando ja esta quase alinhado (@c |d| < 0.1) E a distancia
 * ao jogador supera @c stop_distance — assim o inimigo nao "encosta" no
 * jogador e dispara de longe. O tiro e liberado quando @c cooldown fica
 * negativo, rearmando-o para @c reset; caso contrario o contador decrementa.
 *
 * @param e      Inimigo.
 * @param player Tanque do jogador.
 * @param move   Saida: comando de avanco.
 * @param turn   Saida: comando de giro.
 * @param shot   Saida: disparo.
 * @return Nenhum.
 */
void enemy_ai(Enemy *e, Tank *player, float *move, float *turn, bool *shot)
{
	float dx = player->world.x - e->tank.world.x;
	float dy = player->world.y - e->tank.world.y;
	float target = (-atan2f(dy, dx)) - M_PI * 0.5f;
	float distance = sqrtf(dx * dx + dy * dy);

	float d = target - e->tank.chassi_angle;
	if (d > M_PI) d -= 2.0f * M_PI;
	if (d < -M_PI) d += 2.0f * M_PI;

	*turn = (d > 0) ? 1.0f : -1.0f;

	if (fabsf(d) < 0.1f && distance > e->stop_distance) {
		*move = 1.0f;
	} else {
		*move = 0.0f;
	}

	if (e->cooldown < 0) {
	       *shot = true;
		e->cooldown = e->reset;
	} else {
		*shot = false;
		e->cooldown--;
	}		
}

/**
 * @brief Atualiza o inimigo: roda a IA e aplica os comandos via @c tank_update.
 *
 * Se o inimigo esta @c ACTIVE, obtem os comandos de @c enemy_ai e chama
 * @c tank_update passando @c &player->world como alvo da torre — reutilizando
 * toda a logica de mira do tanque para apontar a torre ao jogador.
 *
 * @param e      Inimigo.
 * @param player Tanque do jogador.
 * @return Nenhum.
 */
void enemy_update(Enemy *e, Tank *player)
{
	float move;
	float turn;
	bool shot;

	if (e->tank.state == ACTIVE) {
		enemy_ai(e, player, &move, &turn, &shot);
		tank_update(&e->tank, move, turn, &player->world, shot);
	}
}

/**
 * @brief Desenha o inimigo apenas enquanto ele estiver @c ACTIVE.
 * @param c Canvas de destino.
 * @param e Inimigo.
 * @return Nenhum.
 */
void enemy_render(Canvas *c, Enemy *e)
{
	if (e->tank.state == ACTIVE) {
		tank_render(c, &e->tank);
	}
}

