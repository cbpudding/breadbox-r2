#include <stdbool.h>

#include "breadbox.h"

int breadbox_init(breadbox_t *engine, breadbox_options_t *options) {
	engine->options = options;
	if(!SDL_Init(SDL_INIT_EVERYTHING)) {
		if(!breadbox_model_init(&engine->model)) {
			if(!breadbox_update_init(&engine->update)) {
				if(!breadbox_subs_init(&engine->subs)) {
					if(!breadbox_view_init(&engine->view, engine->options)) {
						breadbox_log_info(
							BBLOG_BREADBOX,
							"Successfully initialized the engine in %dms",
							SDL_GetTicks()
						);
						return 0;
					} else {
						// I complain about non-specific error messages all the
						// time at my job so why am I doing it here?!? ~Alex
						breadbox_log_error(
							BBLOG_VIEW, "Failed to initialize view"
						);
					}
					breadbox_subs_fini(&engine->subs);
				} else {
					// Yet another comment about myself complaining to myself
					// about non-specific error messages. ~Alex
					breadbox_log_error(
						BBLOG_SUBSCRIPTION, "Failed to initialize subscriptions"
					);
				}
				breadbox_update_fini(&engine->update);
			} else {
				// There's probably a better way of handling this. We should at
				// least say why we can't. ~Alex
				breadbox_log_error(BBLOG_UPDATE, "Failed to initialize update");
			}
			breadbox_model_fini(&engine->model);
		} else {
			// Okay, but why? ~Alex
			breadbox_log_error(BBLOG_MODEL, "Failed to initialize the model");
		}
		SDL_Quit();
	} else {
		breadbox_log_error(
			BBLOG_BREADBOX, "Failed to initialize SDL2: %s", SDL_GetError()
		);
	}
	return 1;
}

void breadbox_fini(breadbox_t *engine) {
	breadbox_view_fini(&engine->view);
	breadbox_subs_fini(&engine->subs);
	breadbox_update_init(&engine->update);
	breadbox_model_fini(&engine->model);
	SDL_Quit();
}

void breadbox_run(breadbox_t *engine) {
	bool alive = true;
	breadbox_msg_t msg;
	while(alive) {
		if(breadbox_subs_poll(&engine->subs, engine->options, &msg)) {
			switch(msg) {
				case BBMSG_QUIT:
					breadbox_log_info(
						BBLOG_BREADBOX,
						"Quit message received. Stopping engine."
					);
					alive = false;
					break;
				case BBMSG_VIEW:
					breadbox_view_render(&engine->view, &engine->model);
					break;
				default:
					breadbox_update_msg(&engine->update, &engine->model, &msg);
					break;
			}
		}
	}
}