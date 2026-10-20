#include "script_entry.h"

extern u8 g_state_02000000[];
extern u8 g_state_02002E34[][6];
extern const u8 g_table_08563A4C[];
extern const u8 g_table_08563A50[];
extern const ScriptEntry g_table_085644FC[];
extern const u8 g_table_08564670[][27];

u32 func_08002804(void);
u8 func_08036330(u8 selector);

void func_080CF7F4(void)
{
    s32 count;
    s32 slot;
    s32 category;
    s32 total;
    s32 identifier;
    s32 remaining;
    u8 threshold;
    u8 *selected;
    const u8 *definition;
    u16 packed_identifier;
    u16 value;

    if (g_state_02000000[0x2190] <= 4)
        return;
    count = 0;
    for (slot = 0; slot < 5; slot++) {
        if (g_state_02000000[0x2E34 + slot * 6] & 7)
            count++;
    }
    if (count > 3)
        return;
    threshold = g_table_08563A4C[count];
    if ((s16)((s16)func_08002804() % 100) > threshold)
        return;
    total = 0;
    for (category = 1; category <= 30; category++) {
        if (func_08036330(category))
            total += g_table_08563A50[category - 1];
    }
    if (total == 0)
        return;
    remaining = (s16)func_08002804() % total;
    for (category = 1; category <= 30; category++) {
        if (func_08036330(category)) {
            remaining -= g_table_08563A50[category - 1];
            if (remaining < 0)
                break;
        }
    }
    if (category == 31)
        return;
    for (slot = 0; slot < 5; slot++) {
        selected = g_state_02002E34[slot];
        if (!(selected[0] & 7))
            break;
    }
    identifier = 0xE1 + category;
    for (count = 0; count < 5; count++) {
        u8 *record = g_state_02002E34[count];

        if ((record[0] & 7) &&
            ((record[2] >> 7) | ((record[3] & 0x7F) << 1)) == identifier)
            return;
    }
    (*(void (**)(void *, s32))0x0836D4B8)(selected, 6);
    definition = g_table_08564670[g_table_085644FC[category].selector];
    selected[0] = (selected[0] & ~7) | ((slot + 1) & 7);
    selected[0] |= 8;
    selected[0] &= ~0x30;
    value = (definition[1] >> 2) & 7;
    selected[0] = (selected[0] & 0x3F) | ((value & 3) << 6);
    selected[1] = (selected[1] & ~3) | ((value >> 2) & 3);
    value = (definition[1] >> 5) | ((definition[2] & 0x1F) << 3);
    if (value & 0x80) {
        value &= ~0x80;
        selected[1] = (selected[1] & ~0x7C) | ((value & 0x1F) << 2);
    } else {
        selected[1] = (selected[1] & ~0x7C) |
                      ((func_08036330(value) & 0x1F) << 2);
    }
    selected[4] = 0;
    selected[5] &= ~1;
    packed_identifier = identifier;
    selected[2] = (selected[2] & 0x7F) | ((packed_identifier & 1) << 7);
    selected[3] = (selected[3] & ~0x7F) | ((packed_identifier >> 1) & 0x7F);
    selected[2] = (selected[2] & ~0x1F) | (func_08036330(category) & 0x1F);
    selected[2] |= 0x20;
    selected[1] |= 0x80;
    selected[5] = (selected[5] & 1) | (6 << 1);
}
