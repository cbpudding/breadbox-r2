#ifndef STAGE_H
#define STAGE_H

#include "plibsys.h"

typedef struct {
    PList *props; // PList<breadbox_prop_t>
} breadbox_stage_t;

int breadbox_stage_init(breadbox_stage_t *stage);
void breadbox_stage_fini(breadbox_stage_t *stage);

#endif