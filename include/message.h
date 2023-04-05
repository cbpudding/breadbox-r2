#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

typedef enum {
    BBMSG_QUIT,
    BBMSG_VIEW
} breadbox_msg_variant_t;

typedef struct {
    uint_fast8_t player;
    uint_least64_t tick;
    breadbox_msg_variant_t variant;
} breadbox_msg_t;

#endif