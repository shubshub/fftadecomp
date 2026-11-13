#include "ffta.h"

typedef struct {
    u32 value;
    u8 unknown_04[0x324];
} Record080C486C;

// Complete [0x080C486C, 0x080C48A4): 56 bytes, 26 instructions.
s16 func_080C486C(void *object, u32 *output)
{
    u32 base = (u32)object;
    s32 index;

    for (index = 0; index < *(u16 *)(base + 0x2964); index++) {
        u32 displacement = index * sizeof(Record080C486C);
        u32 records = base + 0x5C;

        *output++ = *(u32 *)(displacement + records);
    }
    return *(s16 *)(base + 0x2964);
}
