#include "program.h"
#include "raster.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>

/* ---- Internal pipeline context ---- */

typedef struct {
	Canvas *canvas;
	float *z_buffer;
	Shader *shader;
	void *uniform;
	void *vary[3];
	float z[3];
} PipelineCtx;

/* ---- Helpers ---- */

static Vec4 _vec4_mul_mat4(Mat4 M, Vec4 V)
{
	Vec4 ret;
	ret.x = M.m[0][0] * V.x + M.m[0][1] * V.y + M.m[0][2] * V.z + M.m[0][3] * V.w;
	ret.y = M.m[1][0] * V.x + M.m[1][1] * V.y + M.m[1][2] * V.z + M.m[1][3] * V.w;
	ret.z = M.m[2][0] * V.x + M.m[2][1] * V.y + M.m[2][2] * V.z + M.m[2][3] * V.w;
	ret.w = M.m[3][0] * V.x + M.m[3][1] * V.y + M.m[3][2] * V.z + M.m[3][3] * V.w;
	return ret;
}

static bool _clip(Vec4 v)
{
	return fabs(v.x) > 1 || fabs(v.y) > 1 || fabs(v.z) > 1;
}

/* ---- Rasterizer callback (runs per pixel) ---- */

static void pipeline_cb(void *ctx, int x, int y, int u0, int u1, int u2, int det)
{
	PipelineCtx *pc = (PipelineCtx *)ctx;

	if (!canvas_in_bounds(pc->canvas, x, y)) return;

	float w0 = (float)u0 / (float)det;
	float w1 = (float)u1 / (float)det;
	float w2 = (float)u2 / (float)det;

	float z = pc->z[0] * w0 + pc->z[1] * w1 + pc->z[2] * w2;
	size_t idx = pc->canvas->width * y + x;

	if (z >= pc->z_buffer[idx]) return;
	pc->z_buffer[idx] = z;

	FragIn fin = {
		.varyings = { pc->vary[0], pc->vary[1], pc->vary[2] },
		.w = { w0, w1, w2 }
	};

	FragOut fout;
	pc->shader->fsh(&fin, &fout, pc->uniform);

	canvas_set_pixel(pc->canvas, x, y, fout.color);
}

/* ---- Public API ---- */

void renderer_init(Renderer *renderer, Canvas *canvas, float *z_buffer, Mat4 viewport)
{
	renderer->canvas = canvas;
	renderer->z_buffer = z_buffer;
	renderer->viewport = viewport;
}

void renderer_clear(Renderer *renderer, uint32_t color)
{
	canvas_fill(renderer->canvas, color);

	int total = renderer->canvas->width * renderer->canvas->height;

	for (int i = 0; i < total; i++) {
		renderer->z_buffer[i] = FLT_MAX;
	}
}

void renderer_draw(Renderer *renderer, Program *program, Mesh *mesh)
{
	Shader *shader = program->shader;
	void *uniform = program->uniform;

	for (int i = 0; i < mesh->num_faces; i++) {
		Face *face = &mesh->faces[i];

		/* Vertex fetch */

		VertexData vin[3];

		for (int j = 0; j < 3; j++) {
			vin[j].position = mesh->vertices[face->vertex_indices[j] - 1];
			vin[j].normal   = mesh->normals[face->normal_indices[j] - 1];
		}

		/* Vertex shader */

		uint8_t vary_buf[3 * shader->varying_size];

		void *vary[3] = {
			vary_buf,
			vary_buf + shader->varying_size,
			vary_buf + 2 * shader->varying_size
		};

		for (int j = 0; j < 3; j++) {
			shader->vsh(&vin[j], vary[j], uniform);
		}

		/* Clip space: first Vec4 of each varying = clip_pos */

		Vec4 clip[3];

		for (int j = 0; j < 3; j++) {
			clip[j] = *(Vec4 *)vary[j];
			clip[j] = vec4_div_float(clip[j], clip[j].w);
		}

		if (_clip(clip[0]) || _clip(clip[1]) || _clip(clip[2])) {
			continue;
		}

		/* Viewport transform */

		Vec4 screen[3];

		for (int j = 0; j < 3; j++) {
			screen[j] = _vec4_mul_mat4(renderer->viewport, clip[j]);
		}

		/* Back-face culling (screen space) */

		float cross = (screen[1].x - screen[0].x) * (screen[2].y - screen[0].y)
		            - (screen[1].y - screen[0].y) * (screen[2].x - screen[0].x);

		if (cross >= 0) continue;

		/* Rasterize */

		PipelineCtx pctx = {
			.canvas = renderer->canvas,
			.z_buffer = renderer->z_buffer,
			.shader = shader,
			.uniform = uniform,
			.vary = { vary[0], vary[1], vary[2] },
			.z = { clip[0].z, clip[1].z, clip[2].z }
		};

		raster_triangle(
			screen[0].x, screen[0].y,
			screen[1].x, screen[1].y,
			screen[2].x, screen[2].y,
			&pctx, pipeline_cb
		);
	}
}
