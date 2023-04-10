#include <stdlib.h>

#include "physfs.h"

#include "model.h"

int breadbox_model_init(breadbox_model_t *model, char *name) {
    if(PHYSFS_init(name)) {
        if(model->ui = malloc(sizeof(mu_Context))) {
            mu_init(model->ui);
            // ...
            return 0;
        }
        PHYSFS_deinit();
    }
    return 1;
}

void breadbox_model_fini(breadbox_model_t *model) {
    // ...
    free(model->ui);
    PHYSFS_deinit();
}

void breadbox_model_update(breadbox_model_t *model, breadbox_msg_t *msg) {
    // ...
}