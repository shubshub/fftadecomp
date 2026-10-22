#include "ffta.h"

void func_081451C0(u16 value);

void func_081416DC(u16 value)
{
    if (*(const u8 *)0x020084D8 & 1) {
        func_081451C0(value);
        *(u16 *)0x020084D4 = value;
    }
}
