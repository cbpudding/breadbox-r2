#include "breadbox.h"

int main(int argc, char *argv[]) {
    breadbox_t engine;
    breadbox_options_t options;
    breadbox_options_init(&options);
    // ...
    if(!breadbox_init(&engine, &options)) {
        breadbox_run(&engine);
        breadbox_fini(&engine);
    }
    return 0;
}