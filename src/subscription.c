#include "SDL.h"

#include "subscription.h"

int breadbox_subs_init(breadbox_subs_t *subs) {
    subs->tick = 0;
    // ...
    return 0;
}

void breadbox_subs_fini(breadbox_subs_t *subs) {
    // ...
}

int breadbox_subs_poll_sdl(breadbox_subs_t *subs, breadbox_msg_t *msg) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEWHEEL:
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                // TODO: What's the best way to handle inputs here?
                break;
            case SDL_QUIT:
                *msg = BBMSG_QUIT;
                return 1;
            default:
                break;
        }
    }
    return 0;
}

int breadbox_subs_poll(breadbox_subs_t *subs, breadbox_options_t *options, breadbox_msg_t *msg) {
    if(subs->tick < SDL_GetTicks() / (1000 / options->tickrate)) {
        subs->tick++;
        *msg = BBMSG_TICK;
        return 1;
    } else if(breadbox_subs_poll_sdl(subs, msg)) {
        return 1;
    }
    // TODO: Socket stuff for receiving messages from over the network. ~Alex
    // Re-render the result if there's nothing else to do. ~Alex
    *msg = BBMSG_VIEW;
    return 1;
}