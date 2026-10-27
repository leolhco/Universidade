/**
 * @file tank.h
 * @brief Interface do tanque: modelo em espaco LOCAL, render por matrizes e colisao por circulo.
 *
 * Declara a estrutura @c Tank e suas operacoes. O tanque e modelado UMA
 * vez em coordenadas LOCAIS (vertices centrados na origem, gerados na
 * construcao) e, a cada quadro, levado ao espaco de MUNDO por matrizes de
 * transformacao 3x3 (rotacao * translacao). Casco e torre giram de forma
 * INDEPENDENTE: por isso cada um tem seu proprio angulo e e desenhado com
 * uma matriz propria, embora compartilhem o mesmo centro de rotacao.
 *
 * A colisao e tratada de forma analitica aproximando o tanque por um
 * CIRCULO envolvente — barato e invariante a rotacao (o raio nao muda
 * quando o tanque gira), o que e adequado para a jogabilidade.
 */

#ifndef TANK_H
#define TANK_H

#include "canvas.h"
#include "shapes.h"
#include "transform.h"
#include "projectile.h"

/**
 * @brief Quantidade de vertices de cada poligono que compoe o tanque.
 *
 * Sao usados como tamanho dos vetores de vertices (em espaco local) e como
 * limite dos lacos de transformacao/desenho:
 *  - @c CHASSI_N = 4  -> casco (retangulo);
 *  - @c BELT_N   = 4  -> cada esteira (retangulo);
 *  - @c HATCH_N  = 8  -> escotilha (octogono);
 *  - @c TURRET_N = 4  -> torre/canhao (quadrilatero).
 */
#define CHASSI_N 4
#define BELT_N 4
#define HATCH_N 8
#define TURRET_N 4 

/**
 * @brief "Classe" do tanque: geometria local, estado cinematico e de combate.
 */
struct tank {
	Vec2 center;  /**< Posicao de referencia/spawn; origem do deslocamento acumulado. */
	Vec2 size;  /**< Dimensoes base do casco (x = largura, y = altura). */

	float vel;  /**< Velocidade linear (px por unidade de move). */
	float angular;  /**< Incremento angular do casco por unidade de turn (rad). */

	float chassi_angle;  /**< Orientacao atual do casco (rad). */
	Vec2 offset;  /**< Deslocamento acumulado a partir de @c center. */

	Vec2 chassi[CHASSI_N];  /**< Vertices do casco em espaco LOCAL (origem no centro). */
	Vec2 belt_left[CHASSI_N], belt_right[CHASSI_N];  /**< Vertices das esteiras esquerda/direita (local). */
	Vec2 hatch[HATCH_N];  /**< Vertices da escotilha octogonal (local). */
	Vec2 turret[TURRET_N];  /**< Vertices da torre/canhao (local). */

	uint32_t chassi_color;  /**< Cor do casco. */
	uint32_t belt_color;  /**< Cor das esteiras. */
	uint32_t hatch_color;  /**< Cor da escotilha. */
	uint32_t turret_color;  /**< Cor da torre/canhao. */

	float turret_angle;  /**< Orientacao atual da torre (independente do casco). */
	float turret_speed;  /**< Giro maximo da torre por quadro (rad). */
	float target;  /**< Angulo-alvo da torre (mira) calculado no quadro. */

	Vec2 world;  /**< Posicao final em MUNDO (center + offset); base de render e colisao. */

	Projectile projectile;  /**< Municao do tanque (um tiro em voo por vez). */

	int health;  /**< Pontos de vida restantes. */
	int state;  /**< Estado atual (@c ACTIVE ou @c DEAD). */
};
typedef struct tank Tank;

/**
 * @brief Estado de vida do tanque, usado por todo o jogo para pular logica/desenho de mortos.
 */
enum tank_state {
	ACTIVE,
	DEAD
};

/**
 * @brief Construtor do tanque (inicializa geometria local, cinematica e municao).
 *
 * Preenche os campos do tanque, gera os vertices de casco, esteiras,
 * escotilha e canhao em espaco local e inicializa o projetil (cujo raio e
 * derivado da largura da boca do canhao).
 *
 * @param tank         Tanque a inicializar (saida).
 * @param center       Posicao de referencia/spawn no mundo.
 * @param size         Dimensoes base do casco (x = largura, y = altura).
 * @param vel          Velocidade linear por unidade de @c move.
 * @param angular      Incremento angular do casco por unidade de @c turn (rad).
 * @param turret_speed Velocidade maxima de giro da torre por quadro (rad).
 * @param chassi_color Cor do casco.
 * @param belt_color   Cor das esteiras.
 * @param hatch_color  Cor da escotilha.
 * @param turret_color Cor da torre/canhao.
 * @param bounds       Limites do mundo (para o projetil saber quando sair).
 * @param speed        Velocidade do projetil.
 * @param damage       Dano do projetil.
 * @param proj_color   Cor do projetil.
 * @param health       Pontos de vida iniciais.
 * @return Nenhum.
 */
void _tank_(
	  Tank *tank,
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

	  int health
	  );

/**
 * @brief Atualiza a logica do tanque em um quadro (movimento, mira e tiro).
 *
 * @param t     Tanque a atualizar.
 * @param move  Comando de avanco: +1 frente, -1 re, 0 parado.
 * @param turn  Comando de giro do casco: +1/-1.
 * @param mouse Alvo da torre, em coordenadas de mundo (para o jogador, o
 *              cursor; para o inimigo, a posicao do jogador).
 * @param shot  @c true para tentar disparar neste quadro.
 * @return Nenhum.
 */
void tank_update(
		Tank *t,
	       	float move,
	       	float turn,
		Vec2 *mouse,
		bool shot);

/**
 * @brief Desenha o tanque (casco, esteiras, torre, canhao e projetil) no mundo.
 * @param c Canvas de destino.
 * @param t Tanque a desenhar.
 * @return Nenhum.
 */
void tank_render(Canvas *c, Tank *t);

/**
 * @brief Testa se um projetil atingiu um tanque (colisao circulo-circulo).
 * @param p Projetil.
 * @param t Tanque.
 * @return @c true se ha interseccao.
 */
bool check_collision_proj_tank(Projectile *p, Tank *t);

/**
 * @brief Testa sobreposicao entre dois tanques (colisao circulo-circulo).
 * @return @c true se os circulos envolventes se intersectam.
 */
bool check_collision_tank(Tank *t1, Tank *t2);

/**
 * @brief Separa dois tanques sobrepostos empurrando-os ao longo da normal de contato.
 * @return Nenhum.
 */
void resolve_collision_tank(Tank *t1, Tank *t2);

#endif

