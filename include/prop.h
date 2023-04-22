#include "view.h"

#ifndef PROP_H
#define PROP_H

typedef struct breadbox_prop_vertex_t {
	breadbox_vector_t position;
	struct breadbox_prop_vertex_t *next;
} breadbox_prop_vertex_t;

typedef struct breadbox_prop_face_t {
	breadbox_prop_vertex_t *a;
	breadbox_prop_vertex_t *b;
	breadbox_prop_vertex_t *c;
	struct breadbox_prop_face_t *next;
} breadbox_prop_face_t;

typedef struct {
	breadbox_prop_face_t *faces;
	char *path;
	// Reference counting will allow us to reuse props without too much extra
	// memory usage! ~Alex
	int *refcount;
	breadbox_prop_vertex_t *vertices;
	breadbox_matrix_t view;
} breadbox_prop_t;

breadbox_prop_t *breadbox_prop_load(const char *filename);
void breadbox_prop_unload(breadbox_prop_t *prop);

breadbox_prop_t *breadbox_prop_clone(breadbox_prop_t *prop);
void breadbox_prop_view(breadbox_prop_t *prop);

#endif