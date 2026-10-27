/* 0x0800BF04 - 76 bytes: update the two high attribute flags. */
#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 attributes;
} Attributes0800BF04;

void func_0800BF04(Attributes0800BF04 *object, u8 first, u8 second)
{
    if (first)
        object->attributes |= 0x4000;
    else
        object->attributes &= 0xBFFF;

    if (second)
        object->attributes |= 0x8000;
    else
        object->attributes &= 0x7FFF;
}
