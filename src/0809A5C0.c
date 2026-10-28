#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
    u32 flags;
} Object0809A5C0;

/* 0x0809A5C0..0x0809A5E0: 32 bytes, 16 instructions. */
void func_0809A5C0(Object0809A5C0 *object, u8 enabled)
{
    if (enabled) {
        object->flags |= 8;
    } else {
        object->flags &= ~8;
    }
}
