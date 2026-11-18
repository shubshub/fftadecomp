#include "ffta.h"

/* 0x080D3B38..0x080D3B52: 26 bytes. */
typedef struct {
    u8 unknown_00[4];
    u16 flags;
} ObjectState;

extern void *func_080A880C(void *record);

u8 func_080D3B38(void *object)
{
    ObjectState *state = func_080A880C(object);

    if (state->flags & 8)
        return 1;
    return 0;
}
