#ifndef STAGE_H
#define STAGE_H

typedef struct {
    // TODO: Dynamic array of props
} breadbox_stage_t;

int breadbox_stage_init(breadbox_stage_t *stage);
void breadbox_stage_fini(breadbox_stage_t *stage);

#endif