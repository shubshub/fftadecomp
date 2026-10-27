#include "ffta.h"

/* 0x080DD488..0x080DD494: 12 bytes. */
typedef struct {
    u8 unknown_00[0x12];
    u16 value;
} ObjectState;

extern ObjectState *func_080A880C(void *object);

u16 func_080DD488(void *object)
{
    return func_080A880C(object)->value;
}
