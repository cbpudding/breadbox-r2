#include "SDL.h"

#include "breadbox.h"
#include "subscription.h"

int breadbox_subs_init(breadbox_subs_t *subs) {
    PError *error;
    if(subs->sock = p_socket_new(P_SOCKET_FAMILY_INET, P_SOCKET_TYPE_DATAGRAM, P_SOCKET_PROTOCOL_UDP, &error)) {
        // ...
        return 0;
    }
    return 1;
}

void breadbox_subs_fini(breadbox_subs_t *subs) {
    // ...
    p_socket_free(subs->sock);
}

int breadbox_subs_poll_sdl(breadbox_subs_t *subs, breadbox_msg_t *msg) {
    SDL_Event event;
    // All SDL events are from the local machine so the "player" is always
    // us! ~Alex
    // TODO: Will the local player always be 0?
    msg->player = 0;
    msg->tick = SDL_GetTicks64() / BREADBOX_TICK_DURATION;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                // TODO: What's the best way to handle inputs here?
                break;
            case SDL_QUIT:
                msg->variant = BBMSG_QUIT;
                return 1;
            default:
                break;
        }
    }
    return 0;
}

int breadbox_subs_poll(breadbox_subs_t *subs, breadbox_msg_t *msg) {
    if(breadbox_subs_poll_sdl(subs, msg)) {
        return 1;
    }
    // TODO: Socket stuff for receiving messages from over the network. ~Alex
    // Re-render the result if there's nothing else to do. ~Alex
    msg->player = 0;
    msg->tick = SDL_GetTicks64() / BREADBOX_TICK_DURATION;
    msg->variant = BBMSG_VIEW;
    return 1;
}