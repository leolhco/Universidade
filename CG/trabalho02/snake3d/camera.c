#include "camera.h"

void camera_init(Camera *camera, Vec3 eye, Vec3 target, Vec3 up)
{
	camera->eye = eye;
	camera->target = target;
	camera->up = up;
}

static Mat4 mat_look_at(Vec3 eye, Vec3 target, Vec3 up)
{
	Vec3 k = vec3_normalize(vec3_sub_vec3(eye, target));
	Vec3 j = vec3_normalize(vec3_cross_vec3(up, k));
	Vec3 i = vec3_normalize(vec3_cross_vec3(k, j));

	Mat4 rotation = {
		.m = {
			{ j.x, j.y, j.z, 0 },
			{ i.x, i.y, i.z, 0 },
			{ k.x, k.y, k.z, 0 },
			{ 0, 0, 0, 1 }
		}
	};

	Mat4 translation = {
		.m = {
			{ 1, 0, 0, -eye.x },
			{ 0, 1, 0, -eye.y },
			{ 0, 0, 1, -eye.z },
			{ 0, 0, 0, 1 }
		}
	};

	return mat4_mul_mat4(rotation, translation);
}

Mat4 camera_view(Camera *camera)
{
	return mat_look_at(camera->eye, camera->target, camera->up);
}

Vec3 camera_get_forward(Camera *camera)
{
	return vec3_normalize(vec3_sub_vec3(camera->target, camera->eye));
}

Vec3 camera_get_up(Camera *camera)
{
	return vec3_normalize(camera->up);
}

Vec3 camera_get_right(Camera *camera)
{
	Vec3 forward = camera_get_forward(camera);
	Vec3 up = camera_get_up(camera);

	return vec3_normalize(vec3_cross_vec3(forward, up));
}

void camera_move_forward(Camera *camera, float amount)
{
	Vec3 forward = camera_get_forward(camera);

	forward = vec3_mul_float(forward, amount);
	camera->eye = vec3_add_vec3(camera->eye, forward);
	camera->target = vec3_add_vec3(camera->target, forward);
}

void camera_move_backward(Camera *camera, float amount)
{
	camera_move_forward(camera, -amount);
}

void camera_move_right(Camera *camera, float amount)
{
	Vec3 right = camera_get_right(camera); 

	right = vec3_mul_float(right, amount);
	camera->eye = vec3_add_vec3(camera->eye, right);
	camera->target = vec3_add_vec3(camera->target, right);
}

void camera_move_left(Camera *camera, float amount)
{
	camera_move_right(camera, -amount);
}

void camera_move_up(Camera *camera, float amount)
{
	Vec3 up = vec3_mul_float(camera_get_up(camera), amount);

	camera->eye = vec3_add_vec3(camera->eye, up);
	camera->target = vec3_add_vec3(camera->target, up);
}

void camera_move_down(Camera *camera, float amount)
{
	camera_move_up(camera, -amount);
}

void camera_yaw(Camera *camera, float angle)
{
	Vec3 up = camera_get_up(camera);
	Vec3 target_position = vec3_sub_vec3(camera->target, camera->eye);

	target_position = vec3_rotate_by_axis(target_position, up, angle);
	camera->target = vec3_add_vec3(camera->eye, target_position);
}

void camera_pitch(Camera *camera, float angle)
{
	Vec3 right = camera_get_right(camera);
	Vec3 target_position = vec3_sub_vec3(camera->target, camera->eye);

	target_position = vec3_rotate_by_axis(target_position, right, angle);
	camera->target = vec3_add_vec3(camera->eye, target_position);
}

