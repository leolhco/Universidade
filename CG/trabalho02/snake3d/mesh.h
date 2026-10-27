#ifndef MESH_H
#define MESH_H

#include "vec.h"
#include "mat.h"

typedef struct {
	int vertex_indices[3];
	int normal_indices[3];
} Face;

typedef struct {
	int num_vertices;
	int num_normals;
	int num_faces;
	Vec3 *vertices;
	Vec3 *normals;
	Face *faces;
} Mesh;

typedef struct {
	Mesh mesh;
	Vec3 rotation;
	Vec3 scale;
	Vec3 translation;
} Model;

Mat4 model_matrix(Model *model);
void model_set_position(Model *model, Vec3 pos);
void model_rotate_x_axis(Model *model, float angle);
void model_rotate_y_axis(Model *model, float angle);
void model_rotate_z_axis(Model *model, float angle);

#endif
