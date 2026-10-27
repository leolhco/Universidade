#ifndef VEC_H
#define VEC_H

struct vec2 {
	float x, y;
};
typedef struct vec2 Vec2;

struct vec3 {
	float x, y, z;
};
typedef struct vec3 Vec3;

struct vec4 {
	float x, y, z, w;
};
typedef struct vec4 Vec4;

Vec3 vec3_rotate_x_axis(Vec3 vec, float radius);
Vec3 vec3_rotate_y_axis(Vec3 vec, float radius);
Vec3 vec3_rotate_z_axis(Vec3 vec, float radius);
Vec3 vec3_rotate_by_axis(Vec3 v, Vec3 axis, float radius);

Vec3 vec3_mul_float(Vec3 vec, float scalar);
Vec3 vec3_div_float(Vec3 vec, float scalar);
Vec3 vec3_add_vec3(Vec3 lhs, Vec3 rhs);
Vec3 vec3_sub_vec3(Vec3 lhs, Vec3 rhs);

float vec3_dot_vec3(Vec3 lhs, Vec3 rhs);
float vec3_length(Vec3 vec);
Vec3 vec3_normalize(Vec3 vec);
Vec3 vec3_cross_vec3(Vec3 lhs, Vec3 rhs);

Vec4 vec4_mul_float(Vec4 vec, float scalar);
Vec4 vec4_div_float(Vec4 vec, float scalar);

#endif

