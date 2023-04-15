#ifndef UPDATE_H
#define UPDATE_H

#include "message.h"
#include "model.h"

typedef struct {
    // TODO: Script stuff
} breadbox_update_t;

int breadbox_update_init(breadbox_update_t *update);
void breadbox_update_fini(breadbox_update_t *update);

void breadbox_update_msg(breadbox_update_t *update, breadbox_model_t *model, breadbox_msg_t *msg);

#endif