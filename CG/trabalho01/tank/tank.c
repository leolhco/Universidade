/**
 * @file tank.c
 * @brief Implementacao do tanque: pipeline modelo->mundo, mira da torre e colisao.
 *
 * Concentra a matematica grafica do jogo:
 *
 *  - **Transformacao modelo -> mundo.** Os vertices vivem em espaco LOCAL
 *    (centrados na origem). Para desenhar, monta-se uma matriz 3x3
 *    M = rotacao(angulo) * translacao(x, y) e aplica-se a cada vertice via
 *    @c transform(). O efeito e: girar a peca em torno da PROPRIA origem e
 *    so depois move-la para a posicao de mundo — a ordem importa, pois
 *    transladar antes de girar faria a peca orbitar a origem da tela.
 *
 *  - **Casco e torre independentes.** Sao desenhados com duas matrizes
 *    distintas (mesmo centro, angulos diferentes), de modo que a torre
 *    possa apontar para o alvo enquanto o casco aponta para onde anda.
 *
 *  - **Mira com caminho mais curto.** A torre persegue o angulo-alvo
 *    girando sempre pelo menor arco e a uma velocidade limitada.
 *
 *  - **Colisao analitica.** Tanques sao aproximados por circulos
 *    envolventes; a sobreposicao e desfeita empurrando os dois corpos ao
 *    longo da normal de contato.
 *
 * @note Todo o desenho usa apenas primitivas proprias (draw_fill_polygon,
 *       draw_fill_circle) sobre o @c Canvas; a SDL nao participa do
 *       rasterizado.
 */

#include "tank.h"
#include <math.h>

/* === Prototipos internos (forward declarations) ===
 * Geradores de vertices em espaco local (_chassi_/_belt_/_hatch_/_turret_)
 * e utilitarios de transformacao para o mundo. Mantidos @c static para
 * restringir o escopo ao modulo. */
static void _chassi_(Tank *t);
static void _belt_(Tank *t);
static void _turret_(Tank *t);
static void _hatch_(Tank *t);

static Vec2 point_to_world(Vec2 *point, Mat3 M);
static void polygon_to_world(Canvas *canvas, Vec2 *vertices, int num_vertices, Mat3 M, uint32_t color);

/**
 * @brief Construtor do tanque: ver documentacao completa dos parametros em tank.h.
 *
 * Apos copiar os parametros, zera a cinematica (@c offset nulo,
 * @c world = @c center, angulos 0) e gera a geometria local chamando
 * @c _chassi_, @c _belt_, @c _hatch_ e @c _turret_. O raio do projetil e
 * extraido da largura da boca do canhao (@c turret[1].x - @c turret[0].x),
 * para que o tiro nasca proporcional ao cano.
 *
 * @return Nenhum.
 */
void _tank_(
	  Tank *t,
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
	  )
{
	t->center = *center;
	t->size = *size;
	t->vel = vel;
	t->angular = angular;
	t->turret_speed = turret_speed;

	t->chassi_color = chassi_color;
	t->belt_color = belt_color;
	t->hatch_color = hatch_color;
	t->turret_color = turret_color;

	t->offset = (Vec2){ 0.0f, 0.0f };
	t->world = *center;
	t->chassi_angle = 0.0f;
	t->turret_angle = 0.0f;

	t->health = health;
	t->state = ACTIVE;

	_chassi_(t);
	_belt_(t);
	_hatch_(t);
	_turret_(t);

	float radius = (t->turret[1].x - t->turret[0].x) * 0.5f;
	_projectile_(&t->projectile, bounds, radius, speed, damage, proj_color);
}

/**
 * @brief Atualiza movimento do casco, mira da torre e estado do projetil.
 *
 * **Movimento do casco.** O angulo do casco recebe @c turn * @c angular.
 * O avanco e somado ao @c offset na direcao "para frente" do tanque, dada
 * pelo vetor (@c -sin(chassi_angle), @c -cos(chassi_angle)). Essa convencao
 * faz angulo 0 apontar para CIMA (-y na tela) e e a mesma usada pelo
 * projetil, garantindo coerencia. A posicao de mundo e @c center + @c offset
 * (mantemos os vertices locais fixos e movemos apenas a posicao de mundo).
 *
 * **Mira da torre.** Calcula-se o vetor (mouse - tanque) e seu angulo via
 * @c atan2. Esse angulo e convertido para a MESMA convencao do casco
 * (@c -atan2(dy,dx) - @c M_PI/2): a negacao compensa o eixo y da tela
 * apontar para baixo, e o deslocamento de -pi/2 realinha o zero para
 * "cima". A diferenca @c d = alvo - @c turret_angle e normalizada para
 * (-pi, pi], de modo que a torre gire sempre pelo MENOR arco (sem dar a
 * volta toda). Se o alvo esta a menos de @c turret_speed, encaixa direto;
 * caso contrario, gira @c turret_speed no sentido de @c d — limitando a
 * velocidade de giro.
 *
 * **Posicao do disparo.** A boca do canhao (ponto medio de @c turret[2] e
 * @c turret[3], em local) e levada ao mundo pela matriz da torre, para que
 * o projetil nasca exatamente na ponta do cano ja rotacionado.
 *
 * @return Nenhum.
 */
void tank_update(
		Tank *t,
	       	float move,
	       	float turn,
		Vec2 *mouse,
		bool shot)
{
	t->chassi_angle += turn * t->angular;

	float speed = t->vel; 
	float step = move * speed;

	t->offset.x += step * -sinf(t->chassi_angle);
	t->offset.y += step * -cosf(t->chassi_angle);

	t->world.x = t->center.x + t->offset.x;
	t->world.y = t->center.y + t->offset.y;

	float dx = mouse->x - t->world.x; 
	float dy = mouse->y - t->world.y;

	t->target = (-atan2f(dy, dx)) - M_PI * 0.5f;
	float d = t->target - t->turret_angle;

	if (d > M_PI) d -= 2.0f * M_PI;
	if (d < -M_PI) d += 2.0f * M_PI;

	if (fabsf(d) < t->turret_speed) {
		t->turret_angle = t->target;
	} else {
		t->turret_angle += t->turret_speed * (d > 0 ? 1.0f : -1.0f);
	}

	Vec2 pos = { (t->turret[2].x + t->turret[3].x) * 0.5f, (t->turret[2].y + t->turret[3].y) * 0.5f};
	Mat3 M = mul(rotation(t->turret_angle), translation(t->world.x, t->world.y));
	pos = point_to_world(&pos, M);

	projectile_update(&t->projectile, shot, &pos, t->turret_angle);
}

/**
 * @brief Desenha o tanque compondo duas matrizes (casco e torre) e o projetil.
 *
 * Monta M = rotacao(@c chassi_angle) * translacao(@c world) e desenha, nessa
 * ordem, esteira direita, esteira esquerda e casco (a ordem define a
 * sobreposicao: as esteiras ficam sob o casco). Em seguida recompoe M com
 * @c turret_angle (mesma posicao de mundo, angulo da torre) e desenha
 * escotilha e canhao por cima. Por fim renderiza o projetil. As duas
 * matrizes com o mesmo centro e angulos distintos sao o que permite torre e
 * casco girarem de forma independente.
 *
 * @param c Canvas de destino.
 * @param t Tanque a desenhar.
 * @return Nenhum.
 */
void tank_render(Canvas *c, Tank *t)
{
	if (t->state != ACTIVE) return;

	float tx = t->world.x;
	float ty = t->world.y;

	Mat3 M = mul(rotation(t->chassi_angle), translation(tx, ty));

	polygon_to_world(c, t->belt_right, BELT_N, M, t->belt_color);
	polygon_to_world(c, t->belt_left, BELT_N, M, t->belt_color);
	polygon_to_world(c, t->chassi, CHASSI_N, M, t->chassi_color);

	M = mul(rotation(t->turret_angle), translation(tx, ty));
	polygon_to_world(c, t->hatch, HATCH_N, M, t->hatch_color);
	polygon_to_world(c, t->turret, TURRET_N, M, t->turret_color);

	projectile_render(c, &t->projectile);
}

/**
 * @brief Colisao projetil-tanque aproximando o tanque por um circulo envolvente.
 *
 * O raio e metade da altura do casco (@c size.y * 0.5). Usar circulo (em vez
 * do poligono real) torna o teste barato e INVARIANTE A ROTACAO: o tanque
 * girando nao altera o raio, evitando recalcular a forma a cada quadro.
 *
 * @param p Projetil.
 * @param t Tanque.
 * @return @c true se o projetil intersecta o circulo do tanque.
 */
bool check_collision_proj_tank(Projectile *p, Tank *t)
{
	float radius = t->size.y * 0.5f;

	Circle tank = { t->world, radius };

	return circle_in_circle(&p->pos, &tank);
}

/**
 * @brief Colisao tanque-tanque por interseccao dos circulos envolventes.
 * @return @c true se os dois circulos se tocam/sobrepoem.
 */
bool check_collision_tank(Tank *t1, Tank *t2)
{
	float r1 = t1->size.y * 0.5f;
	float r2 = t2->size.y * 0.5f;

	Circle tank1 = { t1->world, r1 }; 
	Circle tank2 = { t2->world, r2 }; 

	return circle_in_circle(&tank1, &tank2);
}

/**
 * @brief Desfaz a sobreposicao entre dois tanques empurrando-os pela normal de contato.
 *
 * Calcula a distancia entre os centros e a penetracao
 * (@c overlap = (r1+r2) - distancia). A direcao de separacao e a normal
 * unitaria n = (dx, dy) / distancia. Cada tanque e deslocado @c overlap/2
 * ao longo de -n e +n respectivamente (correcao dividida igualmente entre
 * os dois), e as posicoes de mundo sao recalculadas a partir do @c offset.
 * Tanques nao-ACTIVE ou ja separados (distancia >= soma dos raios) sao
 * ignorados.
 *
 * @return Nenhum.
 * @warning Divide por @c distancia: se os dois centros coincidirem
 *          exatamente (distancia 0), o resultado e indefinido. Na pratica
 *          a normalizacao por quadro torna esse caso improvavel.
 */
void resolve_collision_tank(Tank *t1, Tank *t2)
{
	if (t1->state != ACTIVE || t2->state != ACTIVE) return;

	float dx = t2->world.x - t1->world.x;
	float dy = t2->world.y - t1->world.y;
	float distance = sqrtf(dx * dx + dy * dy);

	float radius1 = t1->size.y * 0.5f;
	float radius2 = t2->size.y * 0.5f;
	float min_distance = radius1 + radius2;

	if (distance >= min_distance) return;

	float overlap = min_distance - distance;

	float nx = dx / distance;
	float ny = dy / distance;

	float correction = overlap * 0.5f;
	t1->offset.x -= nx * correction;
	t1->offset.y -= ny * correction;
	t2->offset.x += nx * correction;
	t2->offset.y += ny * correction;

	t1->world.x = t1->center.x + t1->offset.x;
	t1->world.y = t1->center.y + t1->offset.y;
	t2->world.x = t2->center.x + t2->offset.x;
	t2->world.y = t2->center.y + t2->offset.y;
}

/**
 * @brief Gera os 4 vertices do casco (retangulo centrado na origem, espaco local).
 *
 * Usa metade da largura/altura (@c hw, @c hh) para posicionar os cantos em
 * torno de (0,0). Centralizar na origem e o que permite, depois, rotacionar
 * o casco em torno do proprio centro via matriz.
 *
 * @param t Tanque cujo vetor @c chassi sera preenchido.
 * @return Nenhum.
 */
static void _chassi_(Tank *t)
{
	Vec2 *size = &t->size;
	Vec2 *out = t->chassi;

	float hw = size->x * 0.5f;
	float hh = size->y * 0.5f;

	out[0] = (Vec2){ -hw, -hh };
	out[1] = (Vec2){ hw, -hh };
	out[2] = (Vec2){ hw, hh };
	out[3] = (Vec2){ -hw, hh};
}

/**
 * @brief Gera os vertices das duas esteiras (retangulos laterais, ligeiramente mais altos que o casco).
 *
 * Cada esteira tem largura @c 0.20 da largura do casco e altura 1.10x a do
 * casco, ladeando o casco a esquerda e a direita em espaco local.
 *
 * @param t Tanque cujos vetores @c belt_left / @c belt_right serao preenchidos.
 * @return Nenhum.
 */
static void _belt_(Tank *t)
{
	Vec2 *size = &t->size;
	Vec2 *left = t->belt_left;
	Vec2 *right = t->belt_right;

	float hw = size->x * 0.5f;
	
	float w_belt = size->x * 0.20f;
	float h_belt = (size->y * 1.10f) * 0.5f;

	left[0] = (Vec2){ -hw - w_belt, -h_belt };
	left[1] = (Vec2){ -hw, -h_belt };
	left[2] = (Vec2){ -hw, h_belt };
	left[3] = (Vec2){ -hw - w_belt, h_belt };

	right[0] = (Vec2){ hw + w_belt, -h_belt };
	right[1] = (Vec2){ hw, -h_belt };
	right[2] = (Vec2){ hw, h_belt };
	right[3] = (Vec2){ hw + w_belt, h_belt };
}

/**
 * @brief Gera a escotilha como um octogono inscrito num circulo de raio @c r (espaco local).
 *
 * Cada vertice e (cos(theta)*r, -sin(theta)*r) com
 * theta = (i + 0.5) * 2*pi/8. O termo +0.5 desloca os vertices em meio
 * setor, deixando o octogono com lados "chatos" no topo/base em vez de um
 * vertice apontado. O sinal negativo em y mantem a convencao de tela
 * (y cresce para baixo).
 *
 * @param t Tanque cujo vetor @c hatch sera preenchido.
 * @return Nenhum.
 */
static void _hatch_(Tank *t)
{
	Vec2 *size = &t->size;
	Vec2 *out = t->hatch;

	float r = ((size->x < size->y) ? size->x : size->y) * 0.35f;

	for (int i = 0; i < HATCH_N; i++) {
		float theta = (i + 0.5f) * 2.0f * M_PI / 8.0f;
		out[i] = (Vec2){ cosf(theta) * r, -sinf(theta) * r };
	}
}

/**
 * @brief Gera o canhao como um quadrilatero que assenta no circulo da escotilha e avanca para frente.
 *
 * A base do cano e apoiada sobre o circulo de raio @c r: o @c apothem
 * (= cos(pi/8) * r) e a distancia do centro ao meio de um lado do octogono,
 * e @c side2 (= sqrt(r^2 - apothem^2)) e a meia-largura desse lado. Assim a
 * base do canhao (@c out[0], @c out[1]) coincide com a aresta superior da
 * escotilha, e a ponta (@c out[2], @c out[3]) se estende ate
 * @c -size.y*(0.5 + 0.25), projetando o cano para frente do tanque.
 *
 * @param t Tanque cujo vetor @c turret sera preenchido.
 * @return Nenhum.
 */
static void _turret_(Tank *t)
{
	Vec2 *size = &t->size;
	Vec2 *out = t->turret;

	float r = ((size->x < size->y) ? size->x : size->y) * 0.35f;
	float apothem = cosf(M_PI / 8.0f) * r;
	float side2 = sqrtf(r * r - apothem * apothem);

	out[0] = (Vec2){ -side2, -apothem };
	out[1] = (Vec2){ side2, -apothem };
	out[2] = (Vec2){ side2, -size->y * (0.5f + 0.25f) };
	out[3] = (Vec2){ -side2, -size->y * (0.5f + 0.25f) };
}

/**
 * @brief Aplica a matriz @p M a um unico ponto, retornando-o em coordenadas de mundo.
 *
 * Copia o ponto e o transforma in-place via @c transform(), sem alterar o
 * original. Usado, por exemplo, para posicionar a boca do canhao no mundo.
 *
 * @param point Ponto em espaco local.
 * @param M     Matriz modelo->mundo (rotacao * translacao).
 * @return O ponto transformado.
 */
static Vec2 point_to_world(Vec2 *point, Mat3 M)
{
	Vec2 ret = *point;

	transform(&ret.x, &ret.y, M);

	return ret;
}

/**
 * @brief Transforma todos os vertices de um poligono para o mundo e o desenha preenchido.
 *
 * Nucleo do pipeline de render: percorre os @p num_vertices em espaco local,
 * leva cada um ao mundo com @c point_to_world(@p M) e passa o resultado para
 * draw_fill_polygon. Usa um array de tamanho variavel (@c ret[num_vertices])
 * como buffer temporario dos vertices transformados, sem alterar os
 * originais (que precisam permanecer em espaco local para o proximo quadro).
 *
 * @param canvas       Canvas de destino.
 * @param vertices     Vertices em espaco local.
 * @param num_vertices Quantidade de vertices.
 * @param M            Matriz modelo->mundo.
 * @param color        Cor de preenchimento.
 * @return Nenhum.
 */
static void polygon_to_world(Canvas *canvas, Vec2 *vertices, int num_vertices, Mat3 M, uint32_t color)
{
	Vec2 ret[num_vertices];

	for (int i = 0; i < num_vertices; i++) {
		ret[i] = point_to_world(vertices + i, M);
	}

	draw_fill_polygon(canvas, ret, num_vertices, color);
}

