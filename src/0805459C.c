#include "ffta.h"

// Complete [0x0805459C, 0x0805463C): 160 bytes, 70 instructions.

typedef struct {
    u8 unknown_00[4];
    u8 present;
    u8 unknown_05[0x28 - 0x05];
    u16 flags;
    u8 unknown_2A[0x102 - 0x2A];
    u8 unknown_102;
    u8 unknown_103;
    u8 unknown_104[0x108 - 0x104];
} Unit0805459C;

typedef struct {
    u8 unknown_00[0x14];
    u8 selected;
} Selection0805459C;

typedef struct {
    u8 unknown_00[0x80];
    Unit0805459C units[24];
    u8 unknown_1940[0x20D0 - 0x1940];
    Selection0805459C selection;
} State0805459C;

typedef struct {
    u8 unknown_00[0x2D3A];
    u8 entries[24];
} Menu0805459C;

extern State0805459C g_state_02000000;
extern Menu0805459C *data_0200F428;
extern void func_08071DC8(u8 selected, u8 *indices);

u8 func_0805459C(void)
{
    Selection0805459C *selection = &g_state_02000000.selection;
    u8 indices[24];
    u8 i;
    u8 count;

    func_08071DC8(selection->selected, indices);
    for (i = 0, count = 0; i < 24; i++) {
        if (indices[i] == 0xFF)
            continue;
        if (g_state_02000000.units[indices[i]].present == 0)
            continue;
        if (g_state_02000000.units[indices[i]].flags & 4)
            continue;
        if (g_state_02000000.units[indices[i]].unknown_102 == 0) {
            if (g_state_02000000.units[indices[i]].unknown_103 == 0)
                continue;
        }
        if (g_state_02000000.units[indices[i]].flags & 0x10)
            continue;
        if (g_state_02000000.units[indices[i]].flags & 8)
            continue;
        data_0200F428->entries[count] = indices[i];
        count++;
    }
    return count;
}
