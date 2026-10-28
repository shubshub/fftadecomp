#include "ffta.h"

typedef struct {
    u8 value;
    u8 unknown_01;
    u16 count;
} SlotEntry;

typedef struct {
    u8 unknown_00[0x2B08];
    SlotEntry entries[64];
} EntryState;

extern EntryState g_state_02000000;

/* Complete [0x080385A8, 0x080385E4): 60 bytes, 26 instructions. */
s32 func_080385A8(u16 value, s32 limit)
{
    s32 count = 0;
    s32 index = 0;
    u8 cleared = 0;
    EntryState *state = &g_state_02000000;

    for (; index < 64; index++) {
        if (state->entries[index].value == value) {
            state->entries[index].value = cleared;
            state->entries[index].count = cleared;
            count++;
            if (count >= limit)
                break;
        }
    }
    return count;
}
