#include <stdbool.h>

#include "breadbox.h"

int breadbox_init(breadbox_t *engine) {
    int ret;
    if(!(ret = SDL_Init(SDL_INIT_EVERYTHING))) {
        if(!(ret = breadbox_model_init(&engine->model))) {
            if(!(ret = breadbox_subs_init(&engine->subs))) {
                if(!(ret = breadbox_view_init(&engine->view))) {
                    return 0;
                }
                breadbox_subs_fini(&engine->subs);
            }
            breadbox_model_fini(&engine->model);
        }
        SDL_Quit();
    }
    return ret;
}

void breadbox_fini(breadbox_t *engine) {
    breadbox_view_fini(&engine->view);
    breadbox_subs_fini(&engine->subs);
    breadbox_model_fini(&engine->model);
    SDL_Quit();
}

void breadbox_run(breadbox_t *engine) {
    bool alive = true;
    breadbox_msg_t msg;
    while(alive) {
        if(breadbox_subs_poll(&engine->subs, &msg)) {
            switch(msg) {
                case BBMSG_QUIT:
                    alive = false;
                    break;
                case BBMSG_VIEW:
                    breadbox_view_render(&engine->view, &engine->model);
                    break;
                default:
                    breadbox_update_msg(&engine->update, &engine->model, &msg);
                    break;
            }
        }
    }
}