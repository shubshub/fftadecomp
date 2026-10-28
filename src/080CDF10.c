#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

static inline void set_flag(u8 *flags, u8 mask, u8 enabled)
{
    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}

void func_080CDF10(Object *object, u8 enabled)
{
    set_flag(&object->flags, 0x80, enabled);
}
