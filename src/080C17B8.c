#include "ffta.h"

extern u8 data_020156C4[];
extern void func_080C7610(u32 value);

/* 080C17B8..080C17C8: 00 B5 02 48 05 F0 28 FF 01 BC 00 47 C4 56 01 02. */
void func_080C17B8(void)
{
    func_080C7610((u32)data_020156C4);
}
