#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F3C];
    u16 entries[20];
} EntryState;

extern EntryState g_state_02000000;

/* 08038628..0803865C: 52 bytes. */
u8 func_08038628(u16 value)
{
    s32 index;

    for (index = 0; index < 20; index++) {
        if (g_state_02000000.entries[index] == 0) {
            g_state_02000000.entries[index] = value;
            return 1;
        }
    }
    return 0;
}
