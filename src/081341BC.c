#include "ffta.h"

/* 0x081341BC..0x081341EA: 46 bytes, 23 instructions. */
typedef struct {
    u8 unknown_00[0xE7];
    u8 classes;
    u8 unknown_E8[0x1C];
    u8 identifier;
} Unit;

u8 func_081341BC(const Unit *source, const Unit *target)
{
    u8 classes;
    u32 first_class;
    u32 second_class;
    u8 identifier;

    if (source == target)
        return 0;
    classes = source->classes;
    first_class = classes & 15;
    second_class = classes >> 4;
    identifier = target->identifier;
    if (first_class == identifier || second_class == identifier)
        return 1;
    return 0;
}
