#include <stdint.h>

#include "breadbox.h"

#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

typedef struct {
	int tick;
	// TODO: Socket stuff
} breadbox_subs_t;

int breadbox_subs_init(breadbox_subs_t *subs);
void breadbox_subs_fini(breadbox_subs_t *subs);

int breadbox_subs_poll(
	breadbox_subs_t *subs, breadbox_options_t *options, breadbox_msg_t *msg
);

#endif