#include "ffta.h"

extern u32 g_state_030034B0;

/* 0x08002830-0x08002838: 8 bytes, including the trailing literal pool. */
u32 *func_08002830(void)
{
    return &g_state_030034B0;
}
