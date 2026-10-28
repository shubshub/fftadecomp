#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1E];
    u8 state;
    u8 unknown_1F[0x11];
    u32 flags;
} Object0809A304;

extern void func_0809801C(Object0809A304 *object);

/* 0x0809A304..0x0809A33E: 58 bytes, 28 instructions. */
void func_0809A304(Object0809A304 *object)
{
    func_0809801C(object);
    if (object->flags & 0x2000) {
        object->state = 14;
    }
    if (object->flags & 0x1000) {
        object->state = 5;
    }
    if (object->flags & 0x40) {
        object->state = 15;
    }
}
