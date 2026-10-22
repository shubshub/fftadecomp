#include "080D1E70.h"

extern const u8 g_table_0855AE4C[][70];

u8 func_080C9540(u16 index);
void func_080C9574(u16 index, u16 enabled);
u8 func_080C95A8(u16 index);
void func_080C95C0(u16 index, u32 value);
void func_080CFA48(u8 index);
void func_080CF118(u8 *record, u8 enabled);

void func_080D1E70(u8 *record, u16 enabled)
{
    u16 identifier = record_identifier(record);
    const u8 *definition = g_table_0855AE4C[identifier];
    s32 slot;

    if (enabled)
        func_080C9574(identifier + 0x2FF, 1);
    for (slot = 0; slot < 2; slot++) {
        s32 adjustment = slot + (enabled ? 0 : 2);
        u16 index = definition[0x12 + 4 * adjustment] |
                    (definition[0x13 + 4 * adjustment] << 8);

        switch (definition[0x14 + 4 * adjustment]) {
        case 1:
            if (index > 0x5FF) {
                u16 value;

                index -= 0x600;
                value = func_080C95A8(index) + (s8)definition[0x15 + 4 * adjustment];
                if (value > 255)
                    value = 255;
                func_080C95C0(index, (u8)value);
            }
            break;
        case 2:
            if (index > 0x5FF) {
                u8 current;
                s8 amount;
                u16 value;

                index -= 0x600;
                current = func_080C95A8(index);
                amount = definition[0x15 + 4 * adjustment];
                if (current > amount)
                    value = current - amount;
                else
                    value = 0;
                func_080C95C0(index, (u8)value);
            }
            break;
        case 3:
            if (index > 0x5FF) {
                index -= 0x600;
                func_080C95C0(index, definition[0x15 + 4 * adjustment]);
            } else {
                if ((s8)definition[0x15 + 4 * adjustment] != 0)
                    func_080C9574(index, 1);
                else
                    func_080C9574(index, 0);
                if ((u16)(index - 0x587) <= 0x17 && !func_080C9540(index))
                    func_080CFA48(index + 0x80);
            }
            break;
        }
    }
    identifier = record_identifier(record);
    if (identifier == 0x6E) {
        if (func_080C95A8(0x81) <= 3)
            func_080C9574(0x582, 1);
        else
            func_080C9574(0x583, 1);
        func_080C95C0(0x81, 0);
    } else if (identifier == 0x2E) {
        func_080C9574(0x36D, 0);
    }
    func_080CF118(record, enabled);
    if (enabled) {
        if (definition[0x3F]) {
            record[2] = (record[2] & ~0x1C) | 0x0C;
            record[3] = definition[0x3F];
        } else {
            remove_record(record);
        }
    } else {
        if (definition[0x40]) {
            record[2] = (record[2] & ~0x1C) | 0x0C;
            record[3] = definition[0x40];
        } else {
            remove_record(record);
        }
    }
}
