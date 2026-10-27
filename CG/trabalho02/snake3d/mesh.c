#include "mesh.h"
#include <math.h>

Mat4 model_matrix(Model *model)
{
	float cx = cosf(model->rotation.x), sx = sinf(model->rotation.x);
	float cy = cosf(model->rotation.y), sy = sinf(model->rotation.y);
	float cz = cosf(model->rotation.z), sz = sinf(model->rotation.z);

	Mat4 S = { .m = {
		{ model->scale.x, 0, 0, 0 },
		{ 0, model->scale.y, 0, 0 },
		{ 0, 0, model->scale.z, 0 },
		{ 0, 0, 0, 1 }
	}};

	Mat4 Rx = { .m = {
		{ 1, 0, 0, 0 },
		{ 0, cx, -sx, 0 },
		{ 0, sx, cx, 0 },
		{ 0, 0, 0, 1 }
	}};

	Mat4 Ry = { .m = {
		{ cy, 0, sy, 0 },
		{ 0, 1, 0, 0 },
		{ -sy, 0, cy, 0 },
		{ 0, 0, 0, 1 }
	}};

	Mat4 Rz = { .m = {
		{ cz, -sz, 0, 0 },
		{ sz, cz, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	}};

	Mat4 T = { .m = {
		{ 1, 0, 0, model->translation.x },
		{ 0, 1, 0, model->translation.y },
		{ 0, 0, 1, model->translation.z },
		{ 0, 0, 0, 1 }
	}};

	return mat4_mul_mat4(T, mat4_mul_mat4(Ry, mat4_mul_mat4(Rx, mat4_mul_mat4(Rz, S))));
}

void model_set_position(Model *model, Vec3 pos)
{
	model->translation = pos;
}

void model_rotate_x_axis(Model *model, float angle)
{
	model->rotation.x += angle;
}

void model_rotate_y_axis(Model *model, float angle)
{
	model->rotation.y += angle;
}

void model_rotate_z_axis(Model *model, float angle)
{
	model->rotation.z += angle;
}
