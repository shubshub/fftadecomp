#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE7];
    u8 current : 4;
    u8 previous : 4;
    u8 unknown_E8[0x1C];
    u8 identity;
} Object08134170;

/* Complete [0x08134170, 0x081341BA): 74 bytes, 37 instructions. */
void func_08134170(Object08134170 *object, Object08134170 *other)
{
    u8 current;
    u8 previous;
    u8 identity;

    if (object == other)
        return;

    current = object->current;
    previous = object->previous;
    identity = other->identity;
    if (current == identity)
        return;

    if (previous == identity) {
        object->current = previous;
        object->previous = current;
    } else {
        object->previous = object->current;
        object->current = identity;
    }
}
