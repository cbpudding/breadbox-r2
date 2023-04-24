#include <string.h>

// More Windows compatibility nonsense... ~Alex
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "GL/gl.h"
#include "physfs.h"

#include "log.h"
#include "prop.h"

breadbox_prop_t *breadbox_prop_load(const char *filename) {
	// ...
}

void breadbox_prop_unload(breadbox_prop_t *prop) {
	// ...
}

breadbox_prop_t *breadbox_prop_clone(breadbox_prop_t *prop) {
	// ...
}

void breadbox_prop_view(breadbox_prop_t *prop) {
	// ...
}