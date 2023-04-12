#include <stdbool.h>

// winsock2 is required for plibsys' sockets on windows
#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

#include "plibsys.h"

#include "breadbox.h"

int breadbox_init(breadbox_t *engine, char *name) {
    int ret;
    p_libsys_init();
    if(!(ret = SDL_Init(SDL_INIT_EVERYTHING))) {
        if(!(ret = breadbox_model_init(&engine->model, name))) {
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
    p_libsys_shutdown();
    return ret;
}

void breadbox_fini(breadbox_t *engine) {
    breadbox_view_fini(&engine->view);
    breadbox_subs_fini(&engine->subs);
    breadbox_model_fini(&engine->model);
    SDL_Quit();
    p_libsys_shutdown();
}

void breadbox_run(breadbox_t *engine) {
    bool alive = true;
    breadbox_msg_t msg;
    while(alive) {
        while(breadbox_subs_poll(&engine->subs, &msg)) {
            switch(msg.variant) {
                case BBMSG_QUIT:
                    alive = false;
                    break;
                case BBMSG_VIEW:
                    breadbox_view_render(&engine->view, &engine->model);
                    break;
                default:
                    breadbox_model_update(&engine->model, &msg);
                    break;
            }
        }
    }
}