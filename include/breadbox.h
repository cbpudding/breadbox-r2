#ifndef BREADBOX_H
#define BREADBOX_H

#define BREADBOX_TICKRATE 30
#define BREADBOX_TICK_DURATION 1000 / BREADBOX_TICKRATE

#include "model.h"
#include "subscription.h"
#include "view.h"

typedef struct {
    breadbox_model_t model;
    breadbox_subs_t subs;
    breadbox_view_t view;
} breadbox_t;

int breadbox_init(breadbox_t *engine);
void breadbox_fini(breadbox_t *engine);

void breadbox_run(breadbox_t *engine);

#endif