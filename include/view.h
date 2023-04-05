#ifndef VIEW_H
#define VIEW_H

#include "microui.h"
#include "SDL.h"

#include "model.h"

typedef struct {
    SDL_GLContext context;
    SDL_Window *window;
} breadbox_view_t;

int breadbox_view_init(breadbox_view_t *view);
void breadbox_view_fini(breadbox_view_t *view);

void breadbox_view_render(breadbox_view_t *view, breadbox_model_t *model);

#endif