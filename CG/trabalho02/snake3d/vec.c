#include "vec.h"
#include <math.h>

Vec3 vec3_rotate_x_axis(Vec3 vec, float radius)
{
	float c = cosf(radius);
	float s = sinf(radius);

	Vec3 ret = {
		.x = vec.x,
		.y = vec.y * c - vec.z * s,
		.z = vec.y * s + vec.z * c
	};

	return ret;
}

Vec3 vec3_rotate_y_axis(Vec3 vec, float radius)
{
	float c = cosf(radius);
	float s = sinf(radius);
	
	Vec3 ret = {
		.x = vec.x * c + vec.z * s,
		.y = vec.y,
		.z = vec.x * (-s) + vec.z * c
	};

	return ret;
}

Vec3 vec3_rotate_z_axis(Vec3 vec, float radius)
{
	float c = cosf(radius);
	float s = sinf(radius);

	Vec3 ret = {
		.x = vec.x * c + vec.y * (-s),
		.y = vec.x * s + vec.y * c,
		.z = vec.z
	};

	return ret;
}

Vec3 vec3_rotate_by_axis(Vec3 v, Vec3 axis, float radius)
{
	axis = vec3_normalize(axis);

	float angleby2 = radius * 0.5f;

	float a = cosf(angleby2);
	float b = axis.x * sinf(angleby2);
	float c = axis.y * sinf(angleby2);
	float d = axis.z * sinf(angleby2);

	float x = v.x, y = v.y, z = v.z;

	Vec3 result = {
		.x = (a * a + b * b - c * c - d * d) * x + 2 * (b * c - a * d) * y + 2 * (b * d + a * c) * z,
		.y = 2 * (b * c + a * d) * x + (a * a + c * c - b * b - d * d) * y + 2 * (c * d - a * b) * z,
		.z = 2 * (b * d - a * c) * x + 2 * (c * d + a * b) * y + (a * a + d * d - b * b - c * c) * z
	};

	return result;
}

Vec3 vec3_add_vec3(Vec3 lhs, Vec3 rhs)
{
	Vec3 ret = {
		.x = lhs.x + rhs.x,
		.y = lhs.y + rhs.y,
		.z = lhs.z + rhs.z
	};

	return ret;
}

Vec3 vec3_sub_vec3(Vec3 lhs, Vec3 rhs)
{
	Vec3 ret = {
		.x = lhs.x - rhs.x,
		.y = lhs.y - rhs.y,
		.z = lhs.z - rhs.z
	};

	return ret;
}

Vec3 vec3_mul_float(Vec3 vec, float scalar)
{
	Vec3 ret = {
		.x = vec.x * scalar,
		.y = vec.y * scalar,
		.z = vec.z * scalar
	};

	return ret;
}

Vec3 vec3_div_float(Vec3 vec, float scalar)
{
	return vec3_mul_float(vec, 1.0f / scalar);
}

float vec3_dot_vec3(Vec3 lhs, Vec3 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float vec3_length(Vec3 vec)
{
	return sqrtf(vec3_dot_vec3(vec, vec));
}

Vec3 vec3_normalize(Vec3 vec)
{
	return vec3_div_float(vec, vec3_length(vec));
}

Vec3 vec3_cross_vec3(Vec3 lhs, Vec3 rhs)
{
	Vec3 ret = {
		.x = lhs.y * rhs.z - rhs.y * lhs.z,
		.y = -(lhs.x * rhs.z - rhs.x * lhs.z),
		.z = lhs.x * rhs.y - rhs.x * lhs.y
	};

	return ret;
}

Vec4 vec4_mul_float(Vec4 vec, float scalar)
{
	Vec4 ret = {
		.x = vec.x * scalar,
		.y = vec.y * scalar,
		.z = vec.z * scalar,
		.w = vec.w * scalar
	};

	return ret;
}

Vec4 vec4_div_float(Vec4 vec, float scalar)
{
	return vec4_mul_float(vec, 1.0f / scalar);
}

