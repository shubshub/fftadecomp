#include "ffta.h"

// Complete [0x08067FFC, 0x0806807C): 128 bytes, 64 instructions.

typedef struct {
    u8 unknown_00[0x108];
} Unit08067FFC;

typedef struct {
    u8 unknown_00[0x14];
    u8 selected;
} SelectionState08067FFC;

extern SelectionState08067FFC g_state_020020D0;
extern Unit08067FFC g_state_02000080[];
extern void func_08071DC8(u8 selected, u8 *indices);
extern u8 func_080C7EA4(const void *unit, u32 selector);

s32 func_08067FFC(Unit08067FFC **output)
{
    u8 indices[24];
    s32 count;
    s32 i;

    func_08071DC8(g_state_020020D0.selected, indices);
    count = 0;

    for (i = 0; i < 24; i++) {
        Unit08067FFC *unit;
        u8 state;

        if (indices[i] == 0xFF)
            continue;
        unit = &g_state_02000080[indices[i]];
        state = func_080C7EA4(unit, 1);
        if (unit != 0 &&
            (state == 2 || state == 8 || state == 0x5E || state == 10 ||
             state == 4 || state == 9 || state == 12))
            continue;
        if (output != 0)
            output[count] = unit;
        count++;
    }
    return count;
}
