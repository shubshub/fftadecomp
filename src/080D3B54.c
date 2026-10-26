#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 flags;
} State;

extern State *func_080A880C(void *object);
extern u8 func_080DD698(void *object, u32 mask);
extern u8 func_080DD494(void *object);

static inline u8 has_blocking_flag(void *object)
{
    State *state = func_080A880C(object);

    if (state->flags & 8)
        return 1;
    return 0;
}

u8 func_080D3B54(void *object)
{
    if (!has_blocking_flag(object) && !func_080DD698(object, 0x20) &&
        !func_080DD494(object))
        return 1;
    return 0;
}
