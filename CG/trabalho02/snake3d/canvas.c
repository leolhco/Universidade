#include "canvas.h"

#define CANVAS_AT(canvas, x, y) \
	( (canvas)->pixels[(canvas)->width * (y) + (x)] )

void canvas_init(Canvas *canvas, uint32_t *pixels, int width, int height)
{
	canvas->pixels = pixels;
	canvas->width = width;
	canvas->height = height;
}

bool canvas_in_bounds(Canvas *canvas, int x, int y)
{
	return (0 <= x && x < canvas->width) && (0 <= y && y < canvas->height);
}

void canvas_set_pixel(Canvas *canvas, int x, int y, uint32_t color)
{
	CANVAS_AT(canvas, x, y) = color;
}

uint32_t canvas_get_pixel(Canvas *canvas, int x, int y)
{
	return CANVAS_AT(canvas, x, y);
}

void canvas_fill(Canvas *canvas, uint32_t color)
{
	for (int i = 0; i < canvas->width * canvas->height; i++) {
		canvas->pixels[i] = color;
	}
}

