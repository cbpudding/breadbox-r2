#include "view.h"

#ifndef PROP_H
#define PROP_H

typedef struct {
	char *path;
	// Reference counting will allow us to reuse props without too much extra
	// memory usage! ~Alex
	int *refcount;
} breadbox_prop_t;

breadbox_prop_t *breadbox_prop_load(const char *filename);
void breadbox_prop_unload(breadbox_prop_t *prop);

breadbox_prop_t *breadbox_prop_clone(breadbox_prop_t *prop);
void breadbox_prop_view(breadbox_prop_t *prop);

#endif