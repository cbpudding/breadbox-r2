#include "breadbox.h"

int main(int argc, char *argv[]) {
	breadbox_t engine;
	breadbox_options_t options;
	breadbox_options_init(&options);
	if(argc > 0) {
		options.meta = argv[0];
	}
	// ...
	if(!breadbox_init(&engine, &options)) {
		breadbox_run(&engine);
		breadbox_fini(&engine);
	}
	return 0;
}