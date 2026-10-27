#include "render_util.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float radians(float degrees)
{
	return (float)M_PI / 180.0f * degrees;
}

Mat4 perspective(float fovy, float aspect, float near, float far)
{
	float c = cosf(fovy * 0.5f) / sinf(fovy * 0.5f);
	float n = near, f = far;

	Mat4 M = { .m = {
		{ c / aspect, 0, 0, 0 },
		{ 0, c, 0, 0 },
		{ 0, 0, (f + n) / (n - f), 2 * f * n / (n - f) },
		{ 0, 0, -1, 0 }
	}};
	return M;
}

Mat4 viewport(int x, int y, int w, int h)
{
	Mat4 M = { .m = {
		{ w * 0.5f, 0, 0, x + w * 0.5f },
		{ 0, -h * 0.5f, 0, y + h * 0.5f },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	}};
	return M;
}

Mat4 mat4_identity(void)
{
	Mat4 M = { .m = {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	}};
	return M;
}

Mat4 mat4_translate(Vec3 t)
{
	Mat4 M = mat4_identity();
	M.m[0][3] = t.x;
	M.m[1][3] = t.y;
	M.m[2][3] = t.z;
	return M;
}

Mat4 mat4_scale(Vec3 s)
{
	Mat4 M = { .m = {
		{ s.x, 0, 0, 0 },
		{ 0, s.y, 0, 0 },
		{ 0, 0, s.z, 0 },
		{ 0, 0, 0, 1 }
	}};
	return M;
}

/* Rotation about an arbitrary unit axis by `angle` (Rodrigues, column form). */
Mat4 mat4_rotate_axis(Vec3 axis, float angle)
{
	axis = vec3_normalize(axis);
	float x = axis.x, y = axis.y, z = axis.z;
	float c = cosf(angle), s = sinf(angle), t = 1.0f - c;

	Mat4 M = { .m = {
		{ t*x*x + c,   t*x*y - s*z, t*x*z + s*y, 0 },
		{ t*x*y + s*z, t*y*y + c,   t*y*z - s*x, 0 },
		{ t*x*z - s*y, t*y*z + s*x, t*z*z + c,   0 },
		{ 0, 0, 0, 1 }
	}};
	return M;
}

Mat4 cube_resting_matrix(Vec3 center, float half)
{
	Mat4 S = mat4_scale((Vec3){ half, half, half });
	Mat4 T = mat4_translate(center);
	return mat4_mul_mat4(T, S);
}

Mat4 cube_rolling_matrix(Vec3 center_a, Vec3 dir, float half, float t)
{
	Vec3 up = { 0, 1, 0 };

	/* Pivot: the bottom edge on the leading side, sitting on the floor. */
	Vec3 pivot = {
		center_a.x + dir.x * half,
		center_a.y - half,
		center_a.z + dir.z * half
	};

	/* Cube center relative to the pivot: half up and half back along -dir. */
	Vec3 rel = {
		-dir.x * half,
		half,
		-dir.z * half
	};

	/* Roll axis is horizontal, perpendicular to the travel direction. */
	Vec3 axis  = vec3_cross_vec3(up, dir);
	float angle = t * (float)M_PI * 0.5f;   /* 0 -> 90 degrees */

	Mat4 S  = mat4_scale((Vec3){ half, half, half });
	Mat4 Tr = mat4_translate(rel);          /* origin -> resting center over pivot */
	Mat4 R  = mat4_rotate_axis(axis, angle);
	Mat4 Tp = mat4_translate(pivot);        /* pivot -> world */

	/* M = Tp * R * Tr * S */
	return mat4_mul_mat4(Tp, mat4_mul_mat4(R, mat4_mul_mat4(Tr, S)));
}

void draw_cube(CubeDrawer *d, Mat4 model, uint32_t color)
{
	PhongUniform u = {
		.mvp          = mat4_mul_mat4(d->proj, mat4_mul_mat4(d->view, model)),
		.model        = model,
		.eye          = d->eye,
		.light_pos    = d->light_pos,
		.color        = color,
		.specular_lut = d->specular_lut
	};

	d->program->shader  = d->shader;
	d->program->uniform = &u;
	renderer_draw(d->renderer, d->program, d->cube);
}
