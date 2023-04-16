#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <stdint.h>

#include "message.h"

typedef struct {
    int tick;
    // TODO: Socket stuff
} breadbox_subs_t;

int breadbox_subs_init(breadbox_subs_t *subs);
void breadbox_subs_fini(breadbox_subs_t *subs);

int breadbox_subs_poll(breadbox_subs_t *subs, breadbox_msg_t *msg);

#endif