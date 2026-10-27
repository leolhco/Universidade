#include "arena.h"

int cell_equal(Cell a, Cell b)
{
	return a.col == b.col && a.row == b.row;
}

Cell cell_step(Cell c, Dir d)
{
	switch (d) {
	case DIR_UP:    c.row -= 1; break;
	case DIR_DOWN:  c.row += 1; break;
	case DIR_LEFT:  c.col -= 1; break;
	case DIR_RIGHT: c.col += 1; break;
	}
	return c;
}

int cell_in_bounds(Cell c)
{
	return c.col >= 0 && c.col < GRID_SIZE
	    && c.row >= 0 && c.row < GRID_SIZE;
}

Vec3 cell_to_world(Cell c)
{
	float half = (GRID_SIZE - 1) * 0.5f;

	Vec3 w = {
		(c.col - half) * CELL_SIZE,
		CUBE_Y,
		(c.row - half) * CELL_SIZE
	};
	return w;
}

Vec3 dir_to_world(Dir d)
{
	switch (d) {
	case DIR_UP:    return (Vec3){  0, 0, -1 };
	case DIR_DOWN:  return (Vec3){  0, 0,  1 };
	case DIR_LEFT:  return (Vec3){ -1, 0,  0 };
	case DIR_RIGHT: return (Vec3){  1, 0,  0 };
	}
	return (Vec3){ 0, 0, 0 };
}

Dir dir_opposite(Dir d)
{
	switch (d) {
	case DIR_UP:    return DIR_DOWN;
	case DIR_DOWN:  return DIR_UP;
	case DIR_LEFT:  return DIR_RIGHT;
	case DIR_RIGHT: return DIR_LEFT;
	}
	return d;
}
