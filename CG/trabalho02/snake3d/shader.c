#include "shader.h"
#include <math.h>

/* ---- Helpers (mat4 * vec4, conversions) ---- */

static Vec4 _vec4_mul_mat4(Mat4 M, Vec4 V)
{
	Vec4 ret;
	ret.x = M.m[0][0] * V.x + M.m[0][1] * V.y + M.m[0][2] * V.z + M.m[0][3] * V.w;
	ret.y = M.m[1][0] * V.x + M.m[1][1] * V.y + M.m[1][2] * V.z + M.m[1][3] * V.w;
	ret.z = M.m[2][0] * V.x + M.m[2][1] * V.y + M.m[2][2] * V.z + M.m[2][3] * V.w;
	ret.w = M.m[3][0] * V.x + M.m[3][1] * V.y + M.m[3][2] * V.z + M.m[3][3] * V.w;
	return ret;
}

static Vec4 _vec3_to_vec4(Vec3 v)
{
	Vec4 ret = { v.x, v.y, v.z, 1 };
	return ret;
}

static Vec4 _vec3_to_vec4w0(Vec3 v)
{
	Vec4 ret = { v.x, v.y, v.z, 0 };
	return ret;
}

static Vec3 _vec4_to_vec3(Vec4 v)
{
	Vec3 ret = { v.x, v.y, v.z };
	return ret;
}

/* ================================================================
 * Default (flat) shader
 * ================================================================ */

static void default_vsh(void *in, void *out, void *uniform)
{
	VertexData *vin = (VertexData *)in;
	DefaultVarying *vout = (DefaultVarying *)out;
	DefaultUniform *u = (DefaultUniform *)uniform;

	vout->clip_pos = _vec4_mul_mat4(u->mvp, _vec3_to_vec4(vin->position));
}

static void default_fsh(void *in, void *out, void *uniform)
{
	(void)in;
	FragOut *fout = (FragOut *)out;
	DefaultUniform *u = (DefaultUniform *)uniform;

	fout->color = u->color;
}

Shader shader_default(void)
{
	Shader s = {
		.vsh = default_vsh,
		.fsh = default_fsh,
		.varying_size = sizeof(DefaultVarying)
	};
	return s;
}

/* ================================================================
 * Phong shader
 * ================================================================ */

static void phong_vsh(void *in, void *out, void *uniform)
{
	VertexData *vin = (VertexData *)in;
	PhongVarying *vout = (PhongVarying *)out;
	PhongUniform *u = (PhongUniform *)uniform;

	Vec4 world = _vec4_mul_mat4(u->model, _vec3_to_vec4(vin->position));

	vout->clip_pos  = _vec4_mul_mat4(u->mvp, _vec3_to_vec4(vin->position));
	vout->world_pos = _vec4_to_vec3(world);
	vout->normal    = _vec4_to_vec3(_vec4_mul_mat4(u->model, _vec3_to_vec4w0(vin->normal)));
}

static void phong_fsh(void *in, void *out, void *uniform)
{
	FragIn *fi = (FragIn *)in;
	FragOut *fout = (FragOut *)out;
	PhongUniform *u = (PhongUniform *)uniform;

	PhongVarying *v0 = (PhongVarying *)fi->varyings[0];
	PhongVarying *v1 = (PhongVarying *)fi->varyings[1];
	PhongVarying *v2 = (PhongVarying *)fi->varyings[2];
	float w0 = fi->w[0], w1 = fi->w[1], w2 = fi->w[2];

	/* Interpola normal */
	Vec3 normal = vec3_add_vec3(
		vec3_mul_float(v0->normal, w0),
		vec3_add_vec3(vec3_mul_float(v1->normal, w1),
		              vec3_mul_float(v2->normal, w2)));

	/* Interpola world_pos */
	Vec3 world_pos = vec3_add_vec3(
		vec3_mul_float(v0->world_pos, w0),
		vec3_add_vec3(vec3_mul_float(v1->world_pos, w1),
		              vec3_mul_float(v2->world_pos, w2)));

	Vec3 light_dir = vec3_normalize(vec3_sub_vec3(u->light_pos, world_pos));
	Vec3 view_dir  = vec3_normalize(vec3_sub_vec3(u->eye, world_pos));

	/* Reflection */
	Vec3 reflection = vec3_normalize(
		vec3_sub_vec3(
			vec3_mul_float(normal, vec3_dot_vec3(normal, light_dir) * 2),
			light_dir));

	float ambient  = 0.1f;
	float diffuse  = fmax(0, vec3_dot_vec3(light_dir, normal));
	float spec_dot = fmax(0, vec3_dot_vec3(reflection, view_dir));
	float specular = u->specular_lut[(int)(spec_dot * 255)];
	float intensity = fmin(1, ambient + diffuse * 0.5f + specular * 0.6f);

	uint8_t R = GET_R(u->color) * intensity;
	uint8_t G = GET_G(u->color) * intensity;
	uint8_t B = GET_B(u->color) * intensity;

	fout->color = RGB(R, G, B);
}

Shader shader_phong(void)
{
	Shader s = {
		.vsh = phong_vsh,
		.fsh = phong_fsh,
		.varying_size = sizeof(PhongVarying)
	};
	return s;
}
