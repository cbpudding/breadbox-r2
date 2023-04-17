#include <stdio.h>

#include "SDL.h"

#include "log.h"

const char *LOGLEVEL_IDENTIFIERS[4] = {
	"DBUG", // BBLOG_DEBUG
	"EROR", // BBLOG_ERROR
	"INFO", // BBLOG_INFO
	"WARN"	// BBLOG_WARNING
};

const char *LOGSOURCE_IDENTIFIERS[5] = {
	"BBOX", // BBLOG_BREADBOX
	"MODL", // BBLOG_MODEL
	"SUBS", // BBLOG_SUBSCRIPTION
	"UPDT", // BBLOG_UPDATE
	"VIEW"	// BBLOG_VIEW
};

void breadbox_log(
	breadbox_logsource_t source,
	breadbox_loglevel_t level,
	const char *format,
	va_list args
) {
	printf(
		"%11.3f %4s %4s ",
		(float)SDL_GetTicks() / 1000.0,
		LOGSOURCE_IDENTIFIERS[source],
		LOGLEVEL_IDENTIFIERS[level]
	);
	vprintf(format, args);
// Gotta make Windows users happy by supporting old TTY standards! ~Alex
#ifdef _WIN32
	printf("\r\n");
#else
	printf("\n");
#endif
	// TODO: Should we log to a file as well? ~Alex
}

void breadbox_log_debug(breadbox_logsource_t source, const char *format, ...) {
	va_list args;
	va_start(args, format);
	breadbox_log(source, BBLOG_DEBUG, format, args);
	va_end(args);
}

void breadbox_log_error(breadbox_logsource_t source, const char *format, ...) {
	va_list args;
	va_start(args, format);
	breadbox_log(source, BBLOG_ERROR, format, args);
	va_end(args);
}

void breadbox_log_info(breadbox_logsource_t source, const char *format, ...) {
	va_list args;
	va_start(args, format);
	breadbox_log(source, BBLOG_INFO, format, args);
	va_end(args);
}

void breadbox_log_warn(
	breadbox_logsource_t source, const char *format, ...
) {
	va_list args;
	va_start(args, format);
	breadbox_log(source, BBLOG_WARNING, format, args);
	va_end(args);
}