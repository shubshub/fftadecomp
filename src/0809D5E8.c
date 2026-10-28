#include "ffta.h"

typedef struct {
    u8 unknown_00[0x29];
    u8 flags;
    u8 unknown_2A[0xB2];
    u16 counter;
} Object0809D5E8;

/* 0x0809D5E8..0x0809D612: 42 bytes, 21 instructions. */
void func_0809D5E8(Object0809D5E8 *object, u32 enabled)
{
    object->counter = 0;
    if (enabled == 0) {
        object->flags |= 1;
    } else {
        object->flags &= ~1;
    }
}
