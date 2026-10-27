#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"
#include "mat.h"

struct camera {
	Vec3 eye;
	Vec3 target;
	Vec3 up;
};
typedef struct camera Camera;

void camera_init(Camera *camera, Vec3 eye, Vec3 target, Vec3 up);
Mat4 camera_view(Camera *camera);
Vec3 camera_get_forward(Camera *camera);
Vec3 camera_get_up(Camera *camera);
Vec3 camera_get_right(Camera *camera);
void camera_move_forward(Camera *camera, float amount);
void camera_move_backward(Camera *camera, float amount);
void camera_move_right(Camera *camera, float amount);
void camera_move_left(Camera *camera, float amount);
void camera_move_up(Camera *camera, float amount);
void camera_move_down(Camera *camera, float amount);
void camera_yaw(Camera *camera, float angle);
void camera_pitch(Camera *camera, float pitch);

#endif

