#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1F64];
    u32 total;
} CounterState0806EBF8;

extern CounterState0806EBF8 g_state_02000000;

/* 0806EBF8..0806EC20: 40 bytes, 13 reachable instructions. */
void func_0806EBF8(u32 amount)
{
    g_state_02000000.total += amount;
    if (g_state_02000000.total > 99999999)
        g_state_02000000.total = 99999999;
}
