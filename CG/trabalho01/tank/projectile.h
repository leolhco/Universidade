/**
 * @file projectile.h
 * @brief Interface do projetil (tiro): circulo em movimento retilineo com tempo de vida.
 *
 * O projetil e um circulo que, ao ser disparado, recebe um vetor velocidade
 * na direcao do canhao e se desloca em linha reta a cada quadro, ate sair
 * dos limites do campo, quando e desativado. Cada tanque possui um unico
 * projetil reutilizavel (so um tiro em voo por vez).
 */

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "canvas.h"
#include "shapes.h"
#include <math.h>

/**
 * @brief Estado de um projetil: geometria, cinematica e dano.
 */
struct projectile {
	Rect bounds;  /**< Limites do campo; fora deles o projetil e desativado. */
	Circle pos;  /**< Posicao (centro) e raio atuais do projetil, em mundo. */
	uint32_t color;  /**< Cor do projetil. */
	float speed;  /**< Modulo da velocidade (px por quadro). */
	Vec2 dv;  /**< Vetor velocidade ja decomposto (dx, dy) na direcao do disparo. */
	bool active;  /**< @c true enquanto o projetil esta em voo. */
	int damage;  /**< Dano aplicado ao tanque atingido. */
};
typedef struct projectile Projectile;

/**
 * @brief Construtor do projetil (inicializa inativo, na origem).
 * @param p      Projetil a inicializar.
 * @param bounds Limites do campo (define quando o tiro "sai" e e desativado).
 * @param radius Raio do projetil.
 * @param speed  Modulo da velocidade.
 * @param damage Dano causado ao acertar.
 * @param color  Cor do projetil.
 * @return Nenhum.
 */
void _projectile_(
		Projectile *p,
		Rect *bounds,
		float radius,
		float speed,
		int damage,
		uint32_t color
		);

/**
 * @brief Atualiza o projetil: dispara (se solicitado e livre) e integra o movimento.
 * @param p     Projetil.
 * @param shot  @c true para disparar (so tem efeito se o projetil estiver inativo).
 * @param pos   Posicao de origem do disparo (boca do canhao, em mundo).
 * @param angle Angulo de disparo (mesma convencao da torre).
 * @return Nenhum.
 */
void projectile_update(
		Projectile *p,
		bool shot,
		Vec2 *pos,
		float angle
		);

/**
 * @brief Desenha o projetil (circulo preenchido) se ele estiver ativo.
 * @param c Canvas de destino.
 * @param p Projetil.
 * @return Nenhum.
 */
void projectile_render(Canvas *c, Projectile *p);

#endif

