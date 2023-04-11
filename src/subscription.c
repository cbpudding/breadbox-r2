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

int breadbox_subs_poll(breadbox_subs_t *subs, breadbox_msg_t *msg) {
    SDL_Event event;
    // Is there a better way to multiplex these queues? ~Alex
    if(SDL_PollEvent(&event)) {
        // All SDL events are from the local machine so the "player" is always
        // us! ~Alex
        // TODO: Will the local player always be 0?
        msg->player = 0;
        msg->tick = SDL_GetTicks64() / BREADBOX_TICK_DURATION;
        switch(event.type) {
            case SDL_KEYDOWN:
                printf("+%02x\n", event.key.keysym.scancode);
                return 0;
            case SDL_KEYUP:
                printf("-%02x\n", event.key.keysym.scancode);
                return 0;
            case SDL_QUIT:
                msg->variant = BBMSG_QUIT;
                break;
            case SDL_WINDOWEVENT:
                switch(event.window.event) {
                    case SDL_WINDOWEVENT_EXPOSED:
                        msg->variant = BBMSG_VIEW;
                        break;
                    default:
                        return 0;
                }
                break;
            default:
                return 0;
        }
        return 1;
    }
    // TODO: Socket stuff for receiving messages from over the network. ~Alex
    return 0;
}