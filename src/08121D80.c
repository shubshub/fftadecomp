#include "ffta.h"

void func_080C95C0(u16 index, u32 value);

void func_08121D80(u8 value)
{
    (*(u8 **)0x020159CC)[0x0F] = value;
    func_080C95C0(20, value);
}
