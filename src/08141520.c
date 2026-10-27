#include "ffta.h"

/* Complete [0x08141520, 0x08141540): 32 bytes, 13 instructions. */
extern u8 data_020084D8;
extern void func_081451C0(u16 value);

void func_08141520(u16 value)
{
    if (data_020084D8 & 2)
        func_081451C0(value);
}
