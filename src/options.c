#include "options.h"

void breadbox_options_init(breadbox_options_t *options) {
    options->fullscreen = false;
    options->height = 240;
    options->name = "Breadbox";
    options->tickrate = 30;
    options->vsync = true;
    options->width = 320;
}