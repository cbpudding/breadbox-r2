#include <stdlib.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "GL/gl.h"

#include "view.h"

int breadbox_view_init(breadbox_view_t *view) {
    // ATI Rage or bust! ~Alex
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    view->window = SDL_CreateWindow(
        "Breadbox",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        320,
        240,
        SDL_WINDOW_OPENGL
    );
    if(view->window) {
        view->context = SDL_GL_CreateContext(view->window);
        if(view->context) {
            return 0;
        }
        SDL_DestroyWindow(view->window);
    }
    return 1;
}

void breadbox_view_fini(breadbox_view_t *view) {
    // ...
    SDL_GL_DeleteContext(view->context);
    SDL_DestroyWindow(view->window);
}

void breadbox_view_render(breadbox_view_t *view, breadbox_model_t *model) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Test triangle to make things less boring. ~Alex
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