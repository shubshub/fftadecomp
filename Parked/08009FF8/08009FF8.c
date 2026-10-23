#include "ffta.h"

u8 func_080C9540(u16 bitIndex);
void func_080C9574(u16 bitIndex, u16 enabled);

void func_08009FF8(void)
{
    if (func_080C9540(0x21F))
        func_080C9574(0x21F, 0);
}
