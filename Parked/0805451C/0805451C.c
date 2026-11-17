#include "ffta.h"

// Complete [0x0805451C, 0x0805459C): 128 bytes, 54 instructions.

typedef struct {
    u8 id;
    u8 unknown_01[0xEB];
    u8 active;
    u8 unknown_ED[0x1B];
} Unit0805451C;

typedef struct {
    u8 unknown_00[0x14];
    u8 selected;
} Selection0805451C;

typedef struct {
    u8 unknown_0000[0x84];
    Unit0805451C units[24];
    u8 unknown_1944[0x78C];
    Selection0805451C selection;
} State0805451C;

typedef struct {
    u8 unknown_0000[0x2D3A];
    u8 indices[24];
} List0805451C;

extern State0805451C g_state_02000000;
extern List0805451C *data_0200F428;
extern void func_08071DC8(u8 selected, u8 *indices);

u8 func_0805451C(void)
{
    u8 indices[24];
    u8 i;
    u8 count;
    Selection0805451C *selection = &g_state_02000000.selection;

    func_08071DC8(selection->selected, indices);
    i = 0;
    count = 0;
    for (; i < 24; i++) {
        if (indices[i] == 0xFF)
            continue;
        if (g_state_02000000.units[indices[i]].id == 0 ||
            g_state_02000000.units[indices[i]].active == 0 ||
            g_state_02000000.units[indices[i]].id == 2 ||
            g_state_02000000.units[indices[i]].id == 15)
            continue;
        data_0200F428->indices[count] = indices[i];
        count++;
    }
    return count;
}
