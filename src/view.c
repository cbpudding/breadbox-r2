#include <stdlib.h>

// Apparently, OpenGL freaks out on Windows if windows.h isn't included. ~Alex
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "GL/gl.h"

#include "log.h"
#include "view.h"

// I hope I did all of this correctly... ~Alex
void mult_matrix_matrix(breadbox_matrix_t *product, breadbox_matrix_t *f1, breadbox_matrix_t *f2) {
	product->a = (f1->a * f2->a) + (f1->e * f2->b) + (f1->i * f2->c) + (f1->m * f2->d);
	product->b = (f1->b * f2->a) + (f1->f * f2->b) + (f1->j * f2->c) + (f1->n * f2->d);
	product->c = (f1->c * f2->a) + (f1->g * f2->b) + (f1->k * f2->c) + (f1->o * f2->d);
	product->d = (f1->d * f2->a) + (f1->h * f2->b) + (f1->l * f2->c) + (f1->p * f2->d);
	product->e = (f1->a * f2->e) + (f1->e * f2->f) + (f1->i * f2->g) + (f1->m * f2->h);
	product->f = (f1->b * f2->e) + (f1->f * f2->f) + (f1->j * f2->g) + (f1->n * f2->h);
	product->g = (f1->c * f2->e) + (f1->g * f2->f) + (f1->k * f2->g) + (f1->o * f2->h);
	product->h = (f1->d * f2->e) + (f1->h * f2->f) + (f1->l * f2->g) + (f1->p * f2->h);
	product->i = (f1->a * f2->i) + (f1->e * f2->j) + (f1->i * f2->k) + (f1->m * f2->l);
	product->j = (f1->b * f2->i) + (f1->f * f2->j) + (f1->j * f2->k) + (f1->n * f2->l);
	product->k = (f1->c * f2->i) + (f1->g * f2->j) + (f1->k * f2->k) + (f1->o * f2->l);
	product->l = (f1->d * f2->i) + (f1->h * f2->j) + (f1->l * f2->k) + (f1->p * f2->l);
	product->m = (f1->a * f2->m) + (f1->e * f2->n) + (f1->i * f2->o) + (f1->m * f2->p);
	product->n = (f1->b * f2->m) + (f1->f * f2->n) + (f1->j * f2->o) + (f1->n * f2->p);
	product->o = (f1->c * f2->m) + (f1->g * f2->n) + (f1->k * f2->o) + (f1->o * f2->p);
	product->p = (f1->d * f2->m) + (f1->h * f2->n) + (f1->l * f2->o) + (f1->p * f2->p);
}

void mult_matrix_vector(breadbox_vector_t *product, breadbox_matrix_t *f1, breadbox_vector_t *f2) {
	product->x = (f1->a * f2->x) + (f1->b * f2->y) + (f1->c * f2->z) + (f1->d * f2->w);
	product->y = (f1->e * f2->x) + (f1->f * f2->y) + (f1->g * f2->z) + (f1->h * f2->w);
	product->z = (f1->i * f2->x) + (f1->j * f2->y) + (f1->k * f2->z) + (f1->l * f2->w);
	product->w = (f1->m * f2->x) + (f1->n * f2->y) + (f1->o * f2->z) + (f1->p * f2->w);
}

void mult_vector_vector(breadbox_vector_t *product, breadbox_vector_t *f1, breadbox_vector_t *f2) {
	product->x = f1->x * f2->x;
	product->y = f1->y * f2->y;
	product->z = f1->z * f2->z;
	product->w = f1->w * f2->w;
}

int breadbox_view_init(breadbox_view_t *view, breadbox_options_t *options) {
	// ATI Rage or bust! ~Alex
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	view->window = SDL_CreateWindow(
		options->name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		options->width,
		options->height,
		SDL_WINDOW_OPENGL
	);
	if(view->window) {
		view->context = SDL_GL_CreateContext(view->window);
		if(view->context) {
			if(SDL_SetRelativeMouseMode(SDL_TRUE)) {
				breadbox_log_warn(
					BBLOG_VIEW, "Failed to capture mouse: %s", SDL_GetError()
				);
			}
			if(SDL_SetWindowFullscreen(
				   view->window, options->fullscreen ? SDL_WINDOW_FULLSCREEN : 0
			   )) {
				breadbox_log_warn(
					BBLOG_VIEW, "Failed to set fullscreen: %s", SDL_GetError()
				);
			}
			if(options->vsync) {
				// Attempt adaptive vsync, if not supported then switch to
				// normal vsync
				if(SDL_GL_SetSwapInterval(-1) == -1) {
					breadbox_log_debug(
						BBLOG_VIEW, "System does not support Adaptive VSync, attempting normal vsync: %s", SDL_GetError()
					);
					if(SDL_GL_SetSwapInterval(1)) {
						breadbox_log_warn(
							BBLOG_VIEW, "Failed to set VSync: %s", SDL_GetError()
						);
					}
				}
			}
			return 0;
		} else {
			breadbox_log_error(
				BBLOG_VIEW,
				"Failed to create OpenGL context: %s",
				SDL_GetError()
			);
		}
		SDL_DestroyWindow(view->window);
	} else {
		// This should alleviate the generic error messages I complained about
		// in breadbox.c. It's not perfect but it's certainly better than
		// nothing. ~Alex
		breadbox_log_error(
			BBLOG_VIEW, "Failed to create window: %s", SDL_GetError()
		);
	}
	return 1;
}

void breadbox_view_fini(breadbox_view_t *view) {
	SDL_GL_DeleteContext(view->context);
	SDL_DestroyWindow(view->window);
}

void breadbox_view_render(breadbox_view_t *view, breadbox_model_t *model) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Test triangle to make things less boring. ~Alex
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRotatef((float)SDL_GetTicks() / 10.0, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0.0, 0.5);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.5, -0.5);
	glEnd();
	// ...
	SDL_GL_SwapWindow(view->window);
}