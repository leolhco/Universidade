#ifndef SHADER_H
#define SHADER_H

#include <stdint.h>
#include <stddef.h>
#include "vec.h"
#include "mat.h"

/* ---- Color macros ---- */

#define MASK8(exp) ( (exp) & 0xFF )

#define RGB(r, g, b) \
	( MASK8(r) << 24 | MASK8(g) << 16 | MASK8(b) << 8 | 0xFF )
#define GET_R(p) ( MASK8(p >> 24) )
#define GET_G(p) ( MASK8(p >> 16) )
#define GET_B(p) ( MASK8(p >>  8) )

/* ---- Vertex data: pipeline -> vertex shader ---- */

typedef struct {
	Vec3 position;
	Vec3 normal;
} VertexData;

/* ---- Fragment I/O: pipeline <-> fragment shader ---- */

typedef struct {
	void *varyings[3];
	float w[3];
} FragIn;

typedef struct {
	uint32_t color;
} FragOut;

/* ---- Shader ---- */

typedef struct {
	void (*vsh)(void *in, void *out, void *uniform);
	void (*fsh)(void *in, void *out, void *uniform);
	size_t varying_size;
} Shader;

/* ---- Default (flat) shader ---- */

typedef struct {
	Vec4 clip_pos;
} DefaultVarying;

typedef struct {
	Mat4 mvp;
	uint32_t color;
} DefaultUniform;

Shader shader_default(void);

/* ---- Phong shader ---- */

typedef struct {
	Vec4 clip_pos;
	Vec3 world_pos;
	Vec3 normal;
} PhongVarying;

typedef struct {
	Mat4 mvp;
	Mat4 model;
	Vec3 eye;
	Vec3 light_pos;
	uint32_t color;
	float *specular_lut;
} PhongUniform;

Shader shader_phong(void);

#endif
