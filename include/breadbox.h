#ifndef BREADBOX_H
#define BREADBOX_H

#define BREADBOX_PORT 1491

#define BREADBOX_MODULE_MODEL 1 << 0
#define BREADBOX_MODULE_VIEW 1 << 1
#define BREADBOX_MODULE_UPDATE 1 << 2
#define BREADBOX_MODULE_SUBSCRIPTION 1 << 3

#include "log.h"
#include "message.h"
#include "model.h"
#include "options.h"
#include "subscription.h"
#include "update.h"
#include "view.h"

typedef struct {
	breadbox_model_t *model;
	int modules;
	breadbox_options_t *options;
	breadbox_subs_t *subs;
	breadbox_update_t *update;
	breadbox_view_t *view;
} breadbox_t;

int breadbox_init(breadbox_t *engine, breadbox_options_t *options);
void breadbox_fini(breadbox_t *engine);

void breadbox_run(breadbox_t *engine);

#endif