#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[0x14];
    s16 first;
    s16 second;
} FlaggedPair;

void func_08021D48(FlaggedPair *object, s16 *first, s16 *second)
{
    *first = object->first;
    *second = object->second;

    if (object->flags & 0x20)
        *first *= -1;
    if (object->flags & 0x200)
        *first *= -1;
    if (object->flags & 0x400)
        *first *= -1;
}
