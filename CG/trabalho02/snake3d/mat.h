#ifndef MAT_H
#define MAT_H

struct mat4 {
	float m[4][4];
};
typedef struct mat4 Mat4;

Mat4 mat4_mul_mat4(Mat4 lhs, Mat4 rhs);

#endif

