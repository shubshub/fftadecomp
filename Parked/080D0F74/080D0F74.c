#include "080D0F74.h"
#include "script_entry.h"

extern u8 g_state_02000000[];
extern const u8 g_table_0855AE4C[][0x46];

u8 func_080C9540(u16 bitIndex);
void func_080C9574(u16 bitIndex, u16 enabled);
u8 func_080C95A8(u16 index);
void func_080C95C0(u16 index, u32 value);
void func_080CFA48(u8 index);
u8 func_08036330(u8 selector);

void func_080D0F74(void *object)
{
    u8 *data = object;

    if (data[3] & 0x80) {
        u16 identifier;
        u8 value;

        data[3] &= ~0x80;
        identifier = data[4] | ((data[5] & 1) << 8);
        if (identifier != 0) {
            const u8 *definition = g_table_0855AE4C[identifier];
            s32 slot;

            if ((data[5] & 0xFE) == 0xC8)
                func_080C9574(identifier + 0x2FF, 1);
            for (slot = 0; slot < 2; slot++) {
                s32 adjustment = slot + ((data[5] & 0xFE) ? 0 : 2);
                u16 index = definition[0x12 + adjustment * 4] |
                            (definition[0x13 + adjustment * 4] << 8);

                switch (definition[0x14 + adjustment * 4]) {
                case 1:
                    if (index > 0x5FF) {
                        u16 amount;

                        index -= 0x600;
                        amount = func_080C95A8(index) +
                                 (s8)definition[0x15 + adjustment * 4];
                        if (amount > 0xFF)
                            amount = 0xFF;
                        func_080C95C0(index, (u8)amount);
                    }
                    break;
                case 2:
                    if (index > 0x5FF) {
                        u16 amount;
                        s32 current;
                        s32 decrement;

                        index -= 0x600;
                        current = func_080C95A8(index);
                        decrement = (s8)definition[0x15 + adjustment * 4];
                        if (current > decrement)
                            amount = current - decrement;
                        else
                            amount = 0;
                        func_080C95C0(index, (u8)amount);
                    }
                    break;
                case 3:
                    if (index > 0x5FF) {
                        index -= 0x600;
                        func_080C95C0(index, definition[0x15 + adjustment * 4]);
                    } else {
                        if ((s8)definition[0x15 + adjustment * 4] != 0)
                            func_080C9574(index, 1);
                        else
                            func_080C9574(index, 0);
                        if ((u16)(index - 0x587) <= 0x17 && !func_080C9540(index))
                            func_080CFA48(index + 0x80);
                    }
                    break;
                }
            }
            identifier = data[4] | ((data[5] & 1) << 8);
            if (identifier == 0x6E) {
                if (func_080C95A8(0x81) <= 3)
                    func_080C9574(0x582, 1);
                else
                    func_080C9574(0x583, 1);
                func_080C95C0(0x81, 0);
            } else if (identifier == 0x2E) {
                func_080C9574(0x36D, 0);
            }
        }
        data[2] = (data[2] & ~0x40) | 0x20;
        data[1] |= 0x80;
        identifier = data[4] | ((data[5] & 1) << 8);
        if (identifier != 0) {
            u8 *record = find_record(((const RecordState *)g_state_02000000)->head, identifier);

            record[2] &= ~0x1C;
        }
        data[5] = (data[5] & 1) | 0xF0;
        identifier = (data[2] >> 7) | ((data[3] & 0x7F) << 1);
        value = func_08036330(g_table_08563A70[identifier].unknown_00);
        data[2] = (data[2] & ~0x1F) | (value & 0x1F);
    } else {
        (*(void (**)(void *, u32))0x0836D4B8)(data, 6);
    }
}
