#include "ffta.h"

extern u32 g_state_030034B0;

/* 0x08002824-0x08002830: 12 bytes, including alignment and the trailing literal pool. */
void func_08002824(u32 value)
{
    g_state_030034B0 = value;
}
