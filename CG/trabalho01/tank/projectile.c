/**
 * @file projectile.c
 * @brief Implementacao do projetil: disparo, movimento retilineo e desativacao ao sair do campo.
 *
 * O disparo define o vetor velocidade a partir do angulo do canhao usando a
 * mesma convencao "para frente" do tanque: (@c -sin(angle), @c -cos(angle)).
 * A cada quadro a posicao e somada a esse vetor (integracao explicita) e,
 * quando o circulo sai dos limites, o projetil e marcado como inativo e fica
 * disponivel para o proximo tiro.
 */

#include "projectile.h"

/**
 * @brief Construtor do projetil: ver parametros em projectile.h.
 *
 * Posiciona o projetil na origem, guarda raio/velocidade/dano/cor e o deixa
 * INATIVO (so passa a existir no mundo quando disparado).
 *
 * @return Nenhum.
 */
void _projectile_(
		Projectile *p,
		Rect *bounds,
		float radius,
		float speed,
		int damage,
		uint32_t color
		)
{
	p->bounds = *bounds;
	p->pos.center.x = 0;
	p->pos.center.y = 0;
	p->pos.radius = radius;
	p->color = color;
	p->speed = speed;
	p->damage = damage;
	p->active = false;
}

/**
 * @brief Dispara (se livre) e avanca o projetil; desativa-o ao sair do campo.
 *
 * Se o projetil esta inativo e @p shot e verdadeiro, ele "nasce" na posicao
 * @p pos e ganha velocidade @c dv = @c speed * (@c -sin(angle), @c -cos(angle))
 * — a mesma direcao para a qual o canhao aponta. Enquanto ativo, soma @c dv a
 * posicao a cada quadro (movimento retilineo uniforme); se o circulo sai dos
 * @c bounds (circle_out_rect), torna-se inativo.
 *
 * @return Nenhum.
 */
void projectile_update(
		Projectile *p,
		bool shot,
		Vec2 *pos,
		float angle
		)
{
	if (!p->active && shot) {
		p->pos.center = *pos;

		p->dv.x = p->speed * -sinf(angle);
		p->dv.y = p->speed * -cosf(angle);
		
		p->active = true;
	}

	if (p->active) {
		p->pos.center.x += p->dv.x;
		p->pos.center.y += p->dv.y;

		if (circle_out_rect(&p->pos, &p->bounds)) {
			p->active = false;
		}
	}
}

/**
 * @brief Desenha o projetil como circulo preenchido, somente quando ativo.
 * @param c Canvas de destino.
 * @param p Projetil.
 * @return Nenhum.
 */
void projectile_render(Canvas *c, Projectile *p)
{
	if (p->active) {
		draw_fill_circle(c, &p->pos, p->color);
	}
}

