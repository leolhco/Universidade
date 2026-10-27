#ifndef PROGRAM_H
#define PROGRAM_H

#include "shader.h"
#include "canvas.h"
#include "mesh.h"

typedef struct {
	Shader *shader;
	void *uniform;
} Program;

typedef struct {
	Canvas *canvas;
	float *z_buffer;
	Mat4 viewport;
} Renderer;

void renderer_init(Renderer *renderer, Canvas *canvas, float *z_buffer, Mat4 viewport);
void renderer_clear(Renderer *renderer, uint32_t color);
void renderer_draw(Renderer *renderer, Program *program, Mesh *mesh);

#endif
