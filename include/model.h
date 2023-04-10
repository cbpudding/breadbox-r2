#ifndef MODEL_H
#define MODEL_H

#include "microui.h"

#include "message.h"

typedef struct {
    mu_Context *ui;
    // TODO: Script stuff
} breadbox_model_t;

int breadbox_model_init(breadbox_model_t *model, char *name);
void breadbox_model_fini(breadbox_model_t *model);

void breadbox_model_update(breadbox_model_t *model, breadbox_msg_t *msg);

#endif