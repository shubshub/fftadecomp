#include "ffta.h"

/* 0x080BC9CC..0x080BC9E4: 24 bytes. */
typedef struct {
    u8 unknown_00[0x180];
    u16 state;
} Context;

u8 func_080BC9CC(const Context *context)
{
    if (context->state == 5)
        return 1;
    return 0;
}
