#include "SDL.h"

#include "model.h"
#include "options.h"

#ifndef VIEW_H
#define VIEW_H

// Technically, this could be float[16] but I'm using letters to preserve what
// little remains of my sanity. ~Alex
typedef struct {
	float a;
	float b;
	float c;
	float d;
	float e;
	float f;
	float g;
	float h;
	float i;
	float j;
	float k;
	float l;
	float m;
	float n;
	float o;
	float p;
} breadbox_matrix_t;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} breadbox_vector_t;

void ident_matrix(breadbox_matrix_t *victim);

void mult_matrix_matrix(
	breadbox_matrix_t *product, breadbox_matrix_t *f1, breadbox_matrix_t *f2
);
void mult_matrix_vector(
	breadbox_vector_t *product, breadbox_matrix_t *f1, breadbox_vector_t *f2
);
void mult_vector_vector(
	breadbox_vector_t *product, breadbox_vector_t *f1, breadbox_vector_t *f2
);

typedef struct {
	SDL_GLContext context;
	SDL_Window *window;
} breadbox_view_t;

int breadbox_view_init(breadbox_view_t *view, breadbox_options_t *options);
void breadbox_view_fini(breadbox_view_t *view);

void breadbox_view_render(breadbox_view_t *view, breadbox_model_t *model);

#endif