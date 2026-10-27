#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
} Descriptor;

extern void func_0800C804(Descriptor *descriptor, u16 *destination, u8 mode);

/* 0800DE40..0800DE62: 34 bytes, 16 instructions. */
void func_0800DE40(Descriptor *descriptors, u16 *destination)
{
    u16 *values = destination;
    Descriptor *descriptor = descriptors;
    s32 index;

    for (index = 0; index < 4; index++) {
        func_0800C804(descriptor, values, 8);
        values++;
        descriptor++;
    }
}
