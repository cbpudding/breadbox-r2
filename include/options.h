#include <stdbool.h>

#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
	// Whether the window should cover the entire screen
	bool fullscreen;
	// The height of the window in pixels
	int height;
	// The value of argv[0] (used for PhysFS)
	char *meta;
	// The title of the window
	char *name;
	// How many times to update the model per second
	int tickrate;
	// Whether to wait for the next vertical blanking interval to display the
	// next frame or not
	bool vsync;
	// The width of the window in pixels
	int width;
} breadbox_options_t;

void breadbox_options_init(breadbox_options_t *options);

#endif