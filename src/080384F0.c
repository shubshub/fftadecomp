#include "ffta.h"

/* 0x080384F0..0x08038524: 52 bytes / 21 instructions. */
typedef struct {
    u8 value;
    u8 unknown_01[3];
} SlotEntry;

typedef struct {
    u8 unknown_00[0x2B08];
    SlotEntry entries[64];
} EntryState;

extern EntryState g_state_02000000;

u8 func_080384F0(u16 value)
{
    s32 index;

    for (index = 0; index < 64; index++) {
        if (g_state_02000000.entries[index].value == 0) {
            g_state_02000000.entries[index].value = value;
            return 1;
        }
    }
    return 0;
}
