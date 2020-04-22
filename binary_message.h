#ifndef MESSAGE_INCLUDED
#define MESSAGE_INCLUDED

#include <stdint.h>

struct binary_message {
    uint8_t* message;
    int length;
};

typedef struct binary_message *binary_message;

#endif