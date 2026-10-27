#include "mat.h"

Mat4 mat4_mul_mat4(Mat4 lhs, Mat4 rhs)
{
	Mat4 ret;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;

			for (int k = 0; k < 4; k++) {
				sum += lhs.m[i][k] *  rhs.m[k][j];
			}

			ret.m[i][j] = sum;
		}
	}

	return ret;
}

