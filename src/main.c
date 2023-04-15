#include "breadbox.h"

int main(int argc, char *argv[]) {
    breadbox_t engine;
    if(!breadbox_init(&engine)) {
        breadbox_run(&engine);
        breadbox_fini(&engine);
    }
    return 0;
}