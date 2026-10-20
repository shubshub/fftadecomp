#include "ffta.h"

extern u8 g_state_02000000[];

void func_080C95C0(u16 index, u32 value)
{
    g_state_02000000[index + 0x2030] = value;
}
