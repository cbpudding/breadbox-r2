#include "stage.h"

int breadbox_stage_init(breadbox_stage_t *stage) {
    // Yes, I know this looks bad...
    // Trust me, this is how it's supposed to work. ~Alex
    stage->props = NULL;
    // ...
    return 0;
}

void breadbox_stage_fini(breadbox_stage_t *stage) {
    // ...
    // TODO: Figure out the best way to free props with p_list_foreach ~Alex
    p_list_free(stage->props);
}