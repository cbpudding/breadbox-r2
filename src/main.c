#include "breadbox.h"

int main(int argc, char *argv[]) {
    breadbox_t engine;
    char *name = argc > 0 ? argv[0] : NULL;
    if(!breadbox_init(&engine, name)) {
        breadbox_run(&engine);
        breadbox_fini(&engine);
    }
    return 0;
}