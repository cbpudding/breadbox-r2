#include <stdlib.h>

#include "physfs.h"

#include "model.h"

int breadbox_model_init(breadbox_model_t *model, char *name) {
    if(PHYSFS_init(name)) {
        if(model->ui = malloc(sizeof(mu_Context))) {
            mu_init(model->ui);
            if(!breadbox_stage_init(&model->stage)) {
                // ...
                return 0;
            }
            free(model->ui);
        }
        PHYSFS_deinit();
    }
    return 1;
}

void breadbox_model_fini(breadbox_model_t *model) {
    // ...
    breadbox_stage_fini(&model->stage);
    free(model->ui);
    PHYSFS_deinit();
}

void breadbox_model_update(breadbox_model_t *model, breadbox_msg_t *msg) {
    // ...
}