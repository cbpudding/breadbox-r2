#include <stdlib.h>

// Apparently, OpenGL freaks out on Windows if windows.h isn't included. ~Alex
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "GL/gl.h"

#include "log.h"
#include "view.h"

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
						breadbox_log_warning(
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