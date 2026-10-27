#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stdbool.h>

struct canvas {
	uint32_t *pixels;
	int width;
	int height;
};
typedef struct canvas Canvas;

void canvas_init(Canvas *canvas, uint32_t *pixels, int width, int height);
bool canvas_in_bounds(Canvas *canvas, int x, int y);
void canvas_set_pixel(Canvas *canvas, int x, int y, uint32_t color);
uint32_t canvas_get_pixel(Canvas *canvas, int x, int y);
void canvas_fill(Canvas *canvas, uint32_t color);

#endif

