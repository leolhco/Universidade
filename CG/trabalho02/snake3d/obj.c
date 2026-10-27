#include "obj.h"
#include <stdlib.h>

void obj_scan(ObjModel *obj, FILE *file)
{
	obj->num_vertices = 0;
	obj->num_normals = 0;
	obj->num_textures = 0;
	obj->num_faces = 0;

	char buffer[256];

	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		if (buffer[0] == 'v') {
			char type = buffer[1];

			if (type == ' ') {
				obj->num_vertices++;
			} else if (type == 't') {
				obj->num_textures++;
			} else if (type == 'n') {
				obj->num_normals++;
			}
		} else if (buffer[0] == 'f') {
			obj->num_faces++;
		}
	}
}

void obj_alloc(ObjModel *obj)
{
	obj->vertices = malloc(sizeof(ObjVertex) * obj->num_vertices);
	obj->textures = malloc(sizeof(ObjTexture) * obj->num_textures);
	obj->normals = malloc(sizeof(ObjNormal) * obj->num_normals);
	obj->faces = malloc(sizeof(ObjFace) * obj->num_faces);
}

void obj_free(ObjModel *obj)
{
	free(obj->vertices);
	free(obj->textures);
	free(obj->normals);
	free(obj->faces);
}

void obj_parse(ObjModel *obj, FILE *file)
{
	char buffer[256];

	ObjVertex *vertice = obj->vertices;
	ObjNormal *normal = obj->normals;
	ObjTexture *texture = obj->textures;
	ObjFace *face = obj->faces;

	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		if (buffer[0] == 'v') {
			char type = buffer[1];

			if (type == ' ') {
				sscanf(buffer + 2, "%f%f%f", &vertice->x, &vertice->y, &vertice->z);
				vertice++;
			} else if (type == 't') {
				sscanf(buffer + 2, "%f%f%f", &texture->u, &texture->v, &texture->w);
				texture++;
			} else if (type == 'n') {
				sscanf(buffer + 2, "%f%f%f", &normal->x, &normal->y, &normal->z);
				normal++;
			}
		} else if (buffer[0] == 'f') {
			int ret = sscanf(buffer + 2, "%d/%d/%d %d/%d/%d %d/%d/%d",
			       &face->vertex_indices[0], &face->texture_indices[0], &face->normal_indices[0],
			       &face->vertex_indices[1], &face->texture_indices[1], &face->normal_indices[1],
			       &face->vertex_indices[2], &face->texture_indices[2], &face->normal_indices[2]
			       );
			     
		       /*	
			if (ret != 2) {
				sscanf(buffer + 2, "%d//%d %d//%d %d//%d",
				       &face->vertex_indices[0], &face->normal_indices[0],
				       &face->vertex_indices[1], &face->normal_indices[1],
				       &face->vertex_indices[2], &face->normal_indices[2]
				      );
			}
			*/

			face++;
		}
	}
}

