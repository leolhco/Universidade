#include "game.h"
#include "shader.h"   /* RGB macro */
#include <stdlib.h>
#include <math.h>

/* ---- Palette ---- */

#define COLOR_FLOOR      RGB( 30,  32,  40)
#define COLOR_WALL       RGB( 70,  74,  90)
#define COLOR_APPLE      RGB(220,  50,  47)
#define COLOR_HEAD       RGB(133, 220,  86)
#define COLOR_BODY       RGB( 99, 153,  34)
#define COLOR_DEAD       RGB(163,  45,  45)

#define MOVE_MS_START    160.0f
#define MOVE_MS_MIN       70.0f
#define MOVE_MS_STEP       6.0f   /* speed-up per apple */

/* ---- Apple ---- */

static void spawn_apple(Game *g)
{
	int free_count = GRID_SIZE * GRID_SIZE - g->snake.length;
	if (free_count <= 0) return;   /* board full: player basically won */

	/* Rejection sampling over cells not covered by the snake. */
	for (;;) {
		Cell c = { rand() % GRID_SIZE, rand() % GRID_SIZE };
		if (!snake_occupies(&g->snake, c)) {
			g->apple = c;
			return;
		}
	}
}

/* ---- Lifecycle ---- */

void game_reset(Game *g)
{
	snake_init(&g->snake);
	g->state      = GAME_RUNNING;
	g->score      = 0;
	g->move_ms    = MOVE_MS_START;
	g->move_accum = 0.0f;
	g->ate_last   = 0;
	spawn_apple(g);
}

void game_init(Game *g)
{
	game_reset(g);
}

void game_input_dir(Game *g, Dir d)
{
	if (g->state == GAME_RUNNING) {
		snake_set_dir(&g->snake, d);
	}
}

/* ---- One logical step ---- */

static void game_step(Game *g)
{
	Cell head = snake_next_head(&g->snake);

	/* Wall collision. */
	if (!cell_in_bounds(head)) {
		g->state = GAME_OVER;
		return;
	}

	int grow = cell_equal(head, g->apple);

	/* Self collision (tail cell is free this step when not growing). */
	if (snake_would_hit_self(&g->snake, head, grow)) {
		g->state = GAME_OVER;
		return;
	}

	snake_step(&g->snake, grow);
	g->ate_last = grow;

	if (grow) {
		g->score++;
		g->move_ms -= MOVE_MS_STEP;
		if (g->move_ms < MOVE_MS_MIN) g->move_ms = MOVE_MS_MIN;
		spawn_apple(g);
	}
}

void game_update(Game *g, float dt_ms)
{
	if (g->state != GAME_RUNNING) return;

	g->move_accum += dt_ms;

	/* Run as many steps as fit in the elapsed time (usually 0 or 1). */
	while (g->state == GAME_RUNNING && g->move_accum >= g->move_ms) {
		g->move_accum -= g->move_ms;
		game_step(g);
	}
}

/* ---- Rendering ---- */

static float clamp01(float t)
{
	if (t < 0) return 0;
	if (t > 1) return 1;
	return t;
}

static void draw_floor_and_walls(Game *g, CubeDrawer *drawer)
{
	(void)g;

	float span = GRID_SIZE * CELL_SIZE;
	float half_span = span * 0.5f;

	/* Floor: one flat cube scaled to cover the whole arena. */
	Mat4 floor_m = mat4_mul_mat4(
		mat4_translate((Vec3){ 0, -0.1f, 0 }),
		mat4_scale((Vec3){ half_span, 0.1f, half_span }));
	draw_cube(drawer, floor_m, COLOR_FLOOR);

	/* Four walls: thin tall cubes framing the arena. */
	float wt = 0.25f;                 /* wall thickness (half-extent) */
	float wh = CUBE_HALF;             /* wall height (half-extent) */
	float edge = half_span + wt;      /* wall center just outside the floor */

	Vec3 wall_scale_x = { half_span + 2 * wt, wh, wt };
	Vec3 wall_scale_z = { wt, wh, half_span + 2 * wt };

	Mat4 north = mat4_mul_mat4(mat4_translate((Vec3){ 0, wh, -edge }), mat4_scale(wall_scale_x));
	Mat4 south = mat4_mul_mat4(mat4_translate((Vec3){ 0, wh,  edge }), mat4_scale(wall_scale_x));
	Mat4 west  = mat4_mul_mat4(mat4_translate((Vec3){ -edge, wh, 0 }), mat4_scale(wall_scale_z));
	Mat4 east  = mat4_mul_mat4(mat4_translate((Vec3){  edge, wh, 0 }), mat4_scale(wall_scale_z));

	draw_cube(drawer, north, COLOR_WALL);
	draw_cube(drawer, south, COLOR_WALL);
	draw_cube(drawer, west,  COLOR_WALL);
	draw_cube(drawer, east,  COLOR_WALL);
}

static void draw_snake(Game *g, CubeDrawer *drawer)
{
	Snake *s = &g->snake;
	int alive = (g->state == GAME_RUNNING);
	float t = alive ? clamp01(g->move_accum / g->move_ms) : 1.0f;

	for (int i = 0; i < s->length; i++) {
		Vec3 from = cell_to_world(s->prev[i]);
		Vec3 to   = cell_to_world(s->body[i]);

		Vec3 delta = vec3_sub_vec3(to, from);
		float dist = vec3_length(delta);

		Mat4 model;

		if (alive && dist > 1e-4f) {
			/* Segment is moving: tumble from its previous cell. */
			Vec3 dir = vec3_div_float(delta, dist);
			model = cube_rolling_matrix(from, dir, CUBE_HALF, t);
		} else {
			/* Stationary (new tail, or game over): rest in place. */
			model = cube_resting_matrix(to, CUBE_HALF);
		}

		uint32_t color;
		if (!alive)      color = COLOR_DEAD;
		else if (i == 0) color = COLOR_HEAD;
		else             color = COLOR_BODY;

		draw_cube(drawer, model, color);
	}
}

static void draw_apple(Game *g, CubeDrawer *drawer)
{
	Vec3 pos = cell_to_world(g->apple);
	/* Slightly smaller cube so the apple reads as distinct from the snake. */
	Mat4 m = cube_resting_matrix(pos, CUBE_HALF * 0.8f);
	draw_cube(drawer, m, COLOR_APPLE);
}

void game_render(Game *g, CubeDrawer *drawer)
{
	draw_floor_and_walls(g, drawer);
	draw_apple(g, drawer);
	draw_snake(g, drawer);
}
