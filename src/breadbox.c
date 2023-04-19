#include <stdbool.h>

#include "physfs.h"

#include "breadbox.h"

int breadbox_init(breadbox_t *engine, breadbox_options_t *options) {
	engine->model = NULL;
	engine->modules = 0;
	engine->options = options;
	engine->subs = NULL;
	engine->update = NULL;
	engine->view = NULL;
	if(SDL_Init(SDL_INIT_EVERYTHING)) {
		breadbox_log_error(
			BBLOG_BREADBOX, "Failed to initialize SDL2: %s", SDL_GetError()
		);
		breadbox_fini(engine);
		return 1;
	}
	if(!PHYSFS_init(options->meta)) {
		breadbox_log_error(
			BBLOG_BREADBOX,
			"Failed to initialize PhysFS: %s",
			PHYSFS_getLastError()
		);
		breadbox_fini(engine);
		return 1;
	}
	engine->model = malloc(sizeof(breadbox_model_t));
	if(!engine->model) {
		breadbox_log_error(
			BBLOG_MODEL, "Not enough memory to allocate the model"
		);
		breadbox_fini(engine);
		return 1;
	}
	if(breadbox_model_init(engine->model)) {
		// Okay, but why? ~Alex
		breadbox_log_error(BBLOG_MODEL, "Failed to initialize the model");
		breadbox_fini(engine);
		return 1;
	}
	engine->modules |= BREADBOX_MODULE_MODEL;
	engine->update = malloc(sizeof(breadbox_update_t));
	if(!engine->update) {
		breadbox_log_error(
			BBLOG_UPDATE, "Not enough memory to allocate update module"
		);
		breadbox_fini(engine);
		return 1;
	}
	if(breadbox_update_init(engine->update)) {
		// There's probably a better way of handling this. We should
		// at least say why we can't. ~Alex
		breadbox_log_error(
			BBLOG_UPDATE, "Failed to initialize the update module"
		);
		breadbox_fini(engine);
		return 1;
	}
	engine->modules |= BREADBOX_MODULE_UPDATE;
	engine->subs = malloc(sizeof(breadbox_subs_t));
	if(!engine->subs) {
		breadbox_log_error(
			BBLOG_SUBSCRIPTION,
			"Not enough memory to allocate the subscription handler"
		);
		breadbox_fini(engine);
		return 1;
	}
	if(breadbox_subs_init(engine->subs)) {
		// Yet another comment about myself complaining to
		// myself about non-specific error messages. ~Alex
		breadbox_log_error(
			BBLOG_SUBSCRIPTION, "Failed to initialize the subscription handler"
		);
		breadbox_fini(engine);
		return 1;
	}
	engine->modules |= BREADBOX_MODULE_SUBSCRIPTION;
	engine->view = malloc(sizeof(breadbox_view_t));
	if(!engine->view) {
		breadbox_log_error(
			BBLOG_VIEW, "Not enough memory to allocate the view function"
		);
		breadbox_fini(engine);
		return 1;
	}
	if(breadbox_view_init(engine->view, engine->options)) {
		// I complain about non-specific error messages all
		// the time at my job so why am I doing it here?!?
		// ~Alex
		breadbox_log_error(
			BBLOG_VIEW, "Failed to initialize the view function"
		);
		breadbox_fini(engine);
		return 1;
	}
	engine->modules |= BREADBOX_MODULE_VIEW;
	breadbox_log_info(
		BBLOG_BREADBOX,
		"Successfully initialized the engine in %dms",
		SDL_GetTicks()
	);
	return 0;
}

void breadbox_fini(breadbox_t *engine) {
	if(engine->modules & BREADBOX_MODULE_VIEW) {
		breadbox_view_fini(engine->view);
	}
	if(engine->view) {
		free(engine->view);
	}
	if(engine->modules & BREADBOX_MODULE_SUBSCRIPTION) {
		breadbox_subs_fini(engine->subs);
	}
	if(engine->subs) {
		free(engine->subs);
	}
	if(engine->modules & BREADBOX_MODULE_UPDATE) {
		breadbox_update_fini(engine->update);
	}
	if(engine->update) {
		free(engine->update);
	}
	if(engine->modules & BREADBOX_MODULE_MODEL) {
		breadbox_model_fini(engine->model);
	}
	if(engine->model) {
		free(engine->model);
	}
	if(PHYSFS_isInit()) {
		PHYSFS_deinit();
	}
	if(SDL_WasInit(0)) {
		SDL_Quit();
	}
}

void breadbox_run(breadbox_t *engine) {
	bool alive = true;
	breadbox_msg_t msg;
	while(alive) {
		if(breadbox_subs_poll(engine->subs, engine->options, &msg)) {
			switch(msg) {
				case BBMSG_QUIT:
					breadbox_log_info(
						BBLOG_BREADBOX,
						"Quit message received. Stopping engine."
					);
					alive = false;
					break;
				case BBMSG_VIEW:
					breadbox_view_render(engine->view, engine->model);
					break;
				default:
					breadbox_update_msg(engine->update, engine->model, &msg);
					break;
			}
		}
	}
}