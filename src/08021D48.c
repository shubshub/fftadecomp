#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[0x14];
    s16 first;
    s16 second;
} FlaggedPair;

/* 0x08021D48..0x08021D96: 78 bytes, 39 instructions. */
void func_08021D48(const void *context, s16 *first, s16 *second)
{
    const FlaggedPair *object = context;

    *first = object->first;
    *second = object->second;

    if (object->flags & 0x20)
        *first *= -1;
    if (object->flags & 0x200)
        *first *= -1;
    if (object->flags & 0x400)
        *first *= -1;
}
