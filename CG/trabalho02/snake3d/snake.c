#include "snake.h"

void snake_init(Snake *s)
{
	s->length   = SNAKE_START_LEN;
	s->dir      = DIR_RIGHT;
	s->next_dir = DIR_RIGHT;

	/* Lay the snake horizontally near the middle, head on the right. */
	int mid = GRID_SIZE / 2;

	for (int i = 0; i < s->length; i++) {
		Cell c = { mid - i, mid };
		s->body[i] = c;
		s->prev[i] = c;
	}
}

void snake_set_dir(Snake *s, Dir d)
{
	/* Reject reversing directly onto the neck. */
	if (d == dir_opposite(s->dir)) return;
	s->next_dir = d;
}

Cell snake_next_head(const Snake *s)
{
	return cell_step(s->body[0], s->next_dir);
}

void snake_step(Snake *s, int grow)
{
	for (int i = 0; i < s->length; i++) {
		s->prev[i] = s->body[i];
	}

	s->dir = s->next_dir;

	if (grow && s->length < SNAKE_MAX) {
		s->length++;
		/* New tail segment starts where the old tail was (no motion). */
		s->prev[s->length - 1] = s->body[s->length - 2];
		s->body[s->length - 1] = s->body[s->length - 2];
	}

	/* Drag body from tail to neck, then place the new head. */
	for (int i = s->length - 1; i > 0; i--) {
		s->body[i] = s->prev[i - 1];
	}
	s->body[0] = cell_step(s->prev[0], s->dir);
}

int snake_would_hit_self(const Snake *s, Cell head, int grow)
{
	/* When not growing, the last segment moves away this step,
	 * so colliding with the current tail cell is fine. */
	int n = grow ? s->length : s->length - 1;

	for (int i = 0; i < n; i++) {
		if (cell_equal(s->body[i], head)) return 1;
	}
	return 0;
}

int snake_occupies(const Snake *s, Cell c)
{
	for (int i = 0; i < s->length; i++) {
		if (cell_equal(s->body[i], c)) return 1;
	}
	return 0;
}
