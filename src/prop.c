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

breadbox_prop_vertex_t *breadbox_prop_load_parse(PHYSFS_File *obj) {
	char *data;
	int len = PHYSFS_fileLength(obj);
	breadbox_prop_vertex_t *next;
	breadbox_prop_vertex_t *root = NULL;
	if(len > 0) {
		breadbox_log_error(
			BBLOG_MODEL, "No data to load prop"
		);
		return NULL;
	}
	data = malloc(len);
	if(!data) {
		// TODO: We should probably print the filename as well for debugging
		// purposes. ~Alex
		breadbox_log_error(
			BBLOG_MODEL, "Failed to allocate memory for prop"
		);
		return NULL;
	}
	if(PHYSFS_read(obj, data, 1, len) < 0) {
		breadbox_log_error(
			BBLOG_MODEL, "Failed to read prop data"
		);
		free(data);
		return NULL;
	}
	// ...
	free(data);
	return root;
}

breadbox_prop_t *breadbox_prop_load(const char *filename) {
	PHYSFS_File *obj;
	breadbox_prop_t *prop;
	if(!PHYSFS_exists(filename)) {
		breadbox_log_error(
			BBLOG_MODEL, "Failed to find prop \"%s\"", filename
		);
		return NULL;
	}
	prop = malloc(sizeof(breadbox_prop_t));
	if(!prop) {
		breadbox_log_error(
			BBLOG_MODEL, "Failed to allocate prop \"%s\"", filename
		);
		return NULL;
	}
	ident_matrix(&prop->view);
	prop->faces = NULL;
	prop->vertices = NULL;
	prop->path = malloc(strlen(filename) + 1);
	if(!prop->path) {
		breadbox_log_error(
			BBLOG_MODEL, "Failed to allocate prop: \"%s\"", filename
		);
		free(prop);
		return NULL;
	}
	// We just ran strlen on this string so this shouldn't cause any issues...
	// right? ~Alex
	strcpy(prop->path, filename);
	prop->refcount = malloc(sizeof(int));
	if(!prop->refcount) {
		breadbox_log_error(
			BBLOG_MODEL, "Failed to allocate prop \"%s\"", filename
		);
		free(prop->path);
		free(prop);
		return NULL;
	}
	*(prop->refcount) = 1;
	obj = PHYSFS_openRead(filename);
	if(!obj) {
		breadbox_log_error(
			BBLOG_MODEL,
			"Failed to load prop \"%s\": %s",
			filename,
			PHYSFS_getLastError()
		);
		breadbox_prop_unload(prop);
		return NULL;
	}
	prop->vertices = breadbox_prop_load_parse(obj);
	if(!prop->vertices) {
		breadbox_log_error(
			BBLOG_MODEL,
			"Failed to load prop data for \"%s\"",
			filename
		);
		breadbox_prop_unload(prop);
		return NULL;
	}
	// ...
	PHYSFS_close(obj);
	return prop;
}

void breadbox_prop_unload(breadbox_prop_t *prop) {
	void *current, *next;
	// Only free the surface-level structure if the underlying data is still
	// referenced! ~Alex
	if(--prop->refcount <= 0) {
		if(prop->faces) {
			current = (void *)prop->faces;
			while(current) {
				next = (void *)((breadbox_prop_face_t *)current)->next;
				free(current);
				current = next;
			}
		}
		if(prop->vertices) {
			current = (void *)prop->vertices;
			while(current) {
				next = (void *)((breadbox_prop_vertex_t *)current)->next;
				free(current);
				current = next;
			}
		}
		free(prop->path);
		free(prop->refcount);
	}
	free(prop);
}

breadbox_prop_t *breadbox_prop_clone(breadbox_prop_t *victim) {
	breadbox_prop_t *doppelganger = malloc(sizeof(breadbox_prop_t));
	if(!doppelganger) {
		breadbox_log_error(
			BBLOG_ERROR, "Failed to clone prop \"%s\"", victim->path
		);
		return NULL;
	}
	memcpy(doppelganger, victim, sizeof(breadbox_prop_t));
	*(victim->refcount)++;
	return doppelganger;
}

void breadbox_prop_view(breadbox_prop_t *prop) {
	breadbox_prop_face_t *face;
	// This function assumes that we are currently rendering triangles.
	// Hopefully, that is the case. ~Alex
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((float *)&prop->view);
	if(prop->faces) {
		face = prop->faces;
		while(face) {
			glVertex3f(
				face->a->position.x, face->a->position.y, face->a->position.z
			);
			glVertex3f(
				face->b->position.x, face->b->position.y, face->b->position.z
			);
			glVertex3f(
				face->c->position.x, face->c->position.y, face->c->position.z
			);
			face = face->next;
		}
	}
}