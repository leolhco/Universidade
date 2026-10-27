#ifndef ARENA_H
#define ARENA_H

#include "vec.h"

/* ---- Grid configuration ---- */

#define GRID_SIZE 15          /* arena is GRID_SIZE x GRID_SIZE cells */
#define CELL_SIZE 1.0f        /* world-space size of one cell */
#define CUBE_HALF 0.42f       /* half-extent of a snake/apple cube (< CELL_SIZE/2) */
#define CUBE_Y (CUBE_HALF)    /* cube center height so its base rests on the floor */

/* ---- Grid types ---- */

typedef struct {
	int col;
	int row;
} Cell;

typedef enum {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
} Dir;

/* ---- Cell helpers ---- */

int  cell_equal(Cell a, Cell b);
Cell cell_step(Cell c, Dir d);
int  cell_in_bounds(Cell c);          /* false => hit a wall */
Vec3 cell_to_world(Cell c);           /* center of the cell at cube height */
Vec3 dir_to_world(Dir d);             /* unit vector on the XZ plane */
Dir  dir_opposite(Dir d);

#endif
