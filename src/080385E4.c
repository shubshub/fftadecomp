#include "ffta.h"

typedef struct {
    u8 value;
    u8 unknown_01;
    u16 count;
} SlotEntry080385E4;

typedef struct {
    u8 unknown_00[0x2B08];
    SlotEntry080385E4 entries[64];
} EntryState080385E4;

extern EntryState080385E4 g_state_02000000;

/* Complete [0x080385E4, 0x08038628): 68 bytes, 27 instructions. */
s32 func_080385E4(u16 value)
{
    s32 count = 0;
    s32 index;

    for (index = 0; index < 64; index++) {
        if (g_state_02000000.entries[index].value == value &&
            g_state_02000000.entries[index].count == 0)
            count++;
    }
    return count;
}
