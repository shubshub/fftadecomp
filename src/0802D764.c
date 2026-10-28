#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x3C32];
    u8 count;
    u8 unknown_3c33;
    u16 entries[256];
} EntryList0802D764;

extern EntryList0802D764 g_state_02000000;

/* 0x0802D764..0x0802D7A0: 60 bytes, including the literal pool. */
u8 func_0802D764(void)
{
    int count = 0;
    int i;

    for (i = 0; i < g_state_02000000.count; i++) {
        if (g_state_02000000.entries[i] != 0)
            count++;
    }
    return count;
}
