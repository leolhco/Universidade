#ifndef SNAKE_H
#define SNAKE_H

#include "arena.h"

#define SNAKE_MAX (GRID_SIZE * GRID_SIZE)
#define SNAKE_START_LEN 3

typedef struct {
	Cell body[SNAKE_MAX];   /* body[0] is the head */
	Cell prev[SNAKE_MAX];   /* positions before the last step (for animation) */
	int  length;
	Dir  dir;               /* current heading */
	Dir  next_dir;          /* buffered heading from input */
} Snake;

void snake_init(Snake *s);

/* Buffer a new heading; ignores 180-degree reversals. */
void snake_set_dir(Snake *s, Dir d);

/* Advance one cell. Copies body into prev first, then moves the head
 * and drags the body. If grow is nonzero the tail is kept (snake grows). */
void snake_step(Snake *s, int grow);

/* Would the head hitting `target` next step be a self-collision?
 * When not growing, the current tail cell is vacated and is allowed. */
int snake_would_hit_self(const Snake *s, Cell head, int grow);

/* Is `c` currently occupied by any body segment? (used for apple spawn) */
int snake_occupies(const Snake *s, Cell c);

Cell snake_next_head(const Snake *s);

#endif
