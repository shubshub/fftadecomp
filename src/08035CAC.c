#include "ffta.h"

extern u32 func_08142AB0(u32, u32);
extern u32 func_08142B28(u32, u32);

/* Complete 08035CAC..08035D00: 84 bytes, including the literal pool. */
void func_08035CAC(u8 *output, u16 value)
{
    u16 base = 0x8118;
    u8 *buffer = output;
    u16 code;

    if (value > 9)
        code = func_08142AB0(value, 10) + base;
    else
        code = base;

    *buffer++ = code >> 8;
    *buffer++ = code;
    code = func_08142B28(value, 10);
    code += base;
    *buffer++ = code >> 8;
    *buffer++ = code;
    *buffer = 0;
}
