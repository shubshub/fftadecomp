#include "ffta.h"

extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0x0813FB7C, 0x0813FBB0), 52 bytes. */
void func_0813FB7C(void *destination, u8 color)
{
    u16 pattern = (color << 12) | (color << 8) | (color << 4) | color;
    /* CpuFill16 supplies one initialized halfword for all 16 transfers. */
    volatile u16 fill = pattern;
    func_0814186C((const void *)&fill, destination, 0x01000010);
}
