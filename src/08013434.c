#include "ffta.h"

struct Context08013434 {
    u8 unknown_00[0x3A];
    u16 flags;
};

extern struct Context08013434 *data_0200918C;

/* Target: 0x08013434..0x0801344C, 24 bytes / 9 instructions. */
void func_08013434(void)
{
    data_0200918C->flags |= 0x200;
}
