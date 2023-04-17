#include <stdarg.h>

#ifndef LOG_H
#define LOG_H

typedef enum {
	BBLOG_DEBUG = 0,
	BBLOG_ERROR,
	BBLOG_INFO,
	BBLOG_WARNING
} breadbox_loglevel_t;

typedef enum {
	// Note: Try to use BBLOG_BREADBOX as little as possible. It should only be
	// used in a case where none of the other sources can be used(pretty much
	// anywhere where something blows up in the glue code). ~Alex
	BBLOG_BREADBOX = 0,
	BBLOG_MODEL,
	BBLOG_SUBSCRIPTION,
	BBLOG_UPDATE,
	BBLOG_VIEW
} breadbox_logsource_t;

void breadbox_log(
	breadbox_logsource_t source,
	breadbox_loglevel_t level,
	const char *format,
	va_list arg
);

void breadbox_log_debug(breadbox_logsource_t source, const char *format, ...);
void breadbox_log_error(breadbox_logsource_t source, const char *format, ...);
void breadbox_log_info(breadbox_logsource_t source, const char *format, ...);
void breadbox_log_warn(breadbox_logsource_t source, const char *format, ...);

#endif