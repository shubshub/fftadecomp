#include "ffta.h"

extern u8 data_020084D8;
extern void func_081452C0(u16 value);

/* Target: [0x08141728, 0x08141748), 32 bytes, 13 instructions. */
void func_08141728(u16 value)
{
    if (data_020084D8 & 1) {
        func_081452C0(value);
    }
}
