#include "ffta.h"

/* Complete [0x08134170, 0x081341BA): 74 bytes, 37 instructions. */
typedef struct {
    u8 unknown_00[0xE7];
    u8 classes;
    u8 unknown_E8[0x1C];
    u8 identifier;
} Unit;

void func_08134170(Unit *source, const Unit *target)
{
    u8 first_class;
    u8 second_class;
    u8 classes;

    if (source == target)
        return;
    first_class = source->classes & 0xF;
    second_class = (source->classes & 0xF0) >> 4;
    if (first_class == target->identifier)
        return;
    if (second_class == target->identifier) {
        source->classes = second_class | (first_class << 4);
    } else {
        /* The ROM narrows the shifted byte to eight bits (lsls #28, lsrs #24)
           and then still masks it with 0xF0. */
        classes = source->classes << 4;
        classes &= 0xF0;
        classes |= target->identifier & 0xF;
        source->classes = classes;
    }
}
