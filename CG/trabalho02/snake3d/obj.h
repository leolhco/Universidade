#ifndef OBJ_H
#define OBJ_H

#include <stdio.h>

struct obj_vertex {
	float x, y, z;
};
typedef struct obj_vertex ObjVertex;

struct obj_normal {
	float x, y, z;
};
typedef struct obj_normal ObjNormal;

struct obj_texture {
	float u, v, w;
};
typedef struct obj_texture ObjTexture;

struct obj_face {
	int vertex_indices[3];
	int texture_indices[3];
	int normal_indices[3];
};
typedef struct obj_face ObjFace;

struct obj_model {
	int num_vertices;
	int num_normals;
	int num_textures;
	int num_faces;

	ObjVertex *vertices;
	ObjTexture *textures;
	ObjNormal *normals;
	ObjFace *faces;	
};
typedef struct obj_model ObjModel;

void obj_scan(ObjModel *obj, FILE *file);
void obj_alloc(ObjModel *obj);
void obj_free(ObjModel *obj);
void obj_parse(ObjModel *obj, FILE *file);

#endif

