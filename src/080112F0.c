/* 0x080112F0 - 76 bytes: update two high attribute flags. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 attributes;
} Attributes080112F0;

void func_080112F0(void *record, u8 first, u8 second)
{
    Attributes080112F0 *object = record;

    if (first)
        object->attributes |= 0x2000;
    else
        object->attributes &= 0xDFFF;

    if (second)
        object->attributes |= 0x4000;
    else
        object->attributes &= 0xBFFF;
}
