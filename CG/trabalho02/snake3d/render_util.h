#ifndef RENDER_UTIL_H
#define RENDER_UTIL_H

#include "vec.h"
#include "mat.h"
#include "mesh.h"
#include "shader.h"
#include "program.h"

/* ---- Math helpers (application level) ---- */

float radians(float degrees);
Mat4  perspective(float fovy, float aspect, float near, float far);
Mat4  viewport(int x, int y, int w, int h);

Mat4  mat4_identity(void);
Mat4  mat4_translate(Vec3 t);
Mat4  mat4_scale(Vec3 s);
Mat4  mat4_rotate_axis(Vec3 axis, float angle);   /* Rodrigues rotation */

/* Model matrix for a cube resting on a cell (centered, scaled, translated). */
Mat4  cube_resting_matrix(Vec3 center, float half);

/* Model matrix for a cube tumbling from cell A toward direction `dir`,
 * pivoting on its leading bottom edge. t in [0,1] drives the 90-degree roll. */
Mat4  cube_rolling_matrix(Vec3 center_a, Vec3 dir, float half, float t);

/* ---- Draw a cube with the Phong shader, given a ready model matrix ---- */

typedef struct {
	Renderer *renderer;
	Program  *program;
	Shader   *shader;
	Mesh     *cube;
	Mat4      view;
	Mat4      proj;
	Vec3      eye;
	Vec3      light_pos;
	float    *specular_lut;
} CubeDrawer;

void draw_cube(CubeDrawer *d, Mat4 model, uint32_t color);

#endif
