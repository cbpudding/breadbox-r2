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

// Callbacks for fast_obj integration with PhysFS ~Alex
void *prop_open(const char *path, void *extra) {
	PHYSFS_File *victim = PHYSFS_openRead(path);
	if(!victim) {
		// Other than logging, I don't think there's much we can do in the case
		// of an error. We're at the mercy of fast_obj here... ~Alex
		breadbox_log_error(
			BBLOG_MODEL,
			"Failed to open \"%s\": %s",
			path,
			#if (PHYSFS_VER_MAJOR < 3) && (PHYSFS_VER_MINOR < 1)
			PHYSFS_getLastError()
			#else
			PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())
			#endif
		);
	}
	return (void *)victim;
}

void prop_close(void *file, void *path) {
	PHYSFS_close((PHYSFS_File *)file);
}

size_t prop_read(void *file, void *dst, size_t bytes, void *path) {
	#if (PHYSFS_VER_MAJOR < 3) && (PHYSFS_VER_MINOR < 1)
	PHYSFS_sint64 length = PHYSFS_read((PHYSFS_File *)file, dst, 1, bytes);
	#else
	PHYSFS_sint64 length = PHYSFS_readBytes((PHYSFS_File *)file, dst, bytes);
	#endif
	if(length < 0) {
		breadbox_log_error(
			BBLOG_MODEL,
			"Failed to read \"%s\": %s",
			path,
			// Not sure how this makes the API better but having an actual
			// error code can be nice. ~Alex
			#if (PHYSFS_VER_MAJOR < 3) && (PHYSFS_VER_MINOR < 1)
			PHYSFS_getLastError()
			#else
			PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())
			#endif
		);
		// Just to be safe! ~Alex
		length = 0;
	}
	return (size_t)length;
}

unsigned long prop_size(void *file, void *path) {
	// This is probably fine... right? ~Alex
	return (unsigned long)PHYSFS_fileLength((PHYSFS_File *)file);
}

// As long as the ABI doesn't change, this should work. ~Alex
const fastObjCallbacks PROP_CALLBACKS = {
	prop_open,
	prop_close,
	prop_read,
	prop_size
};

fastObjMesh *prop_load(const char *path) {
	return fast_obj_read_with_callbacks(path, &PROP_CALLBACKS, (void *)path);
}

// And back to your regularly scheduled programming! ~Alex
breadbox_prop_t *breadbox_prop_load(const char *filename) {
	breadbox_prop_t *prop = malloc(sizeof(breadbox_prop_t));
	if(!prop) {
		breadbox_log_error(BBLOG_MODEL, "Failed to allocate view matrix for \"%s\"", filename);
		return NULL;
	}
	mat4_identity((mfloat_t *)&prop->view);
	prop->refcount = malloc(sizeof(int));
	if(!prop->refcount) {
		breadbox_log_error(BBLOG_MODEL, "Failed to allocate reference counter for \"%s\"", filename);
		free(prop);
		return NULL;
	}
	*(prop->refcount) = 1;
	prop->path = malloc(strlen(filename) + 1);
	if(!prop->path) {
		breadbox_log_error(BBLOG_MODEL, "Failed to allocate path for \"%s\"", filename);
		free(prop->refcount);
		free(prop);
	}
	// We just ran strlen on the filename so this should be valid. ~Alex
	strcpy(prop->path, filename);
	prop->mesh = prop_load(filename);
	if(!prop->mesh) {
		breadbox_log_error(BBLOG_MODEL, "Failed to load mesh for \"%s\"", filename);
		free(prop->path);
		free(prop->refcount);
		free(prop);
		return NULL;
	}
	return prop;
}

void breadbox_prop_unload(breadbox_prop_t *prop) {
	*(prop->refcount)--;
	if(*(prop->refcount) < 1) {
		fast_obj_destroy(prop->mesh);
		free(prop->path);
		free(prop->refcount);
	}
	free(prop);
}

breadbox_prop_t *breadbox_prop_clone(breadbox_prop_t *prop) {
	breadbox_prop_t *doppelganger = malloc(sizeof(breadbox_prop_t));
	if(!doppelganger) {
		breadbox_log_error(BBLOG_MODEL, "Failed to clone \"%s\": Not enough memory", prop->path);
		return NULL;
	}
	memcpy(doppelganger, prop, sizeof(breadbox_prop_t));
	*(prop->refcount)++;
	return doppelganger;
}

void breadbox_prop_view(breadbox_prop_t *prop) {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((GLfloat *)&prop->view);
	// ...
}