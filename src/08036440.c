#include "ffta.h"

typedef struct {
    u8 active : 1;
    u8 unknown_00_1 : 7;
    u8 unknown_01[2];
    u8 value;
    u8 unknown_04[0x30];
} FlaggedRow;

typedef struct {
    u8 unknown_00[0x7B8];
    FlaggedRow entries[6];
} State;

extern State *g_state_03002810;

u32 func_08036440(u8 value, u32 mode)
{
    s32 index;

    if (value == 0)
        return 0;
    if (mode == 1) {
        if (g_state_03002810->entries[0].value == value - 1)
            return 1;
    } else {
        index = mode != 0;
        for (; index <= 5; index++) {
            if (g_state_03002810->entries[index].active &&
                g_state_03002810->entries[index].value == value - 1)
                return 1;
        }
    }
    return 0;
}
