/* 0x0800C628 - 36 bytes: set or clear attribute bit 2. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u16 attributes;
} Attributes0800C628;

void func_0800C628(Attributes0800C628 *object, u8 enabled)
{
    if (enabled)
        object->attributes |= 4;
    else
        object->attributes &= 0xFFFB;
}
