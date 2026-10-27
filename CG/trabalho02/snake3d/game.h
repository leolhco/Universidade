#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "arena.h"
#include "render_util.h"

typedef enum {
	GAME_RUNNING,
	GAME_OVER
} GameState;

typedef struct {
	Snake     snake;
	Cell      apple;
	GameState state;
	int       score;

	float move_ms;      /* time between logical steps (lower = faster) */
	float move_accum;   /* accumulated time toward the next step */
	int   ate_last;     /* did the snake grow on the most recent step */
} Game;

void game_init(Game *g);
void game_reset(Game *g);

/* Feed a direction request from input. */
void game_input_dir(Game *g, Dir d);

/* Advance the simulation by dt milliseconds. */
void game_update(Game *g, float dt_ms);

/* Draw the whole scene (floor, walls, apple, snake) using the drawer. */
void game_render(Game *g, CubeDrawer *drawer);

#endif
