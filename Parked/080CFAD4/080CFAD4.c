#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 unknown_02[10];
} FlagRecord;

extern FlagRecord g_state_02002CC0[];
extern const u8 g_table_08565416[][38];

u32 func_08002804(void);
u8 func_080C95A8(u16 index);
void func_080C95C0(u16 index, u32 value);
void func_080C9574(u16 bitIndex, u16 enabled);

u8 func_080CFAD4(u8 *output, u8 clear_count)
{
    s32 appended;
    s32 index;
    u8 snapshot_count;
    FlagRecord *record;

    (*(void (**)(void *, s32))0x0836D4B8)(output, clear_count);
    appended = 0;
    snapshot_count = 0;
    record = g_state_02002CC0;
    for (index = 0; index < 30; index++) {
        if ((record->flags & 1) && (record->flags & 2))
            snapshot_count++;
        record++;
    }
    if (snapshot_count > 30)
        snapshot_count = 30;
    for (index = 6; index < 30; index++) {
        const u8 *definition = g_table_08565416[index];
        s32 counter_index = index + 0x15;

        record = &g_state_02002CC0[index];
        if (record->flags & 1) {
            if (record->flags & 8) {
                u8 remaining = func_080C95A8(counter_index);

                if (remaining != 0 && --remaining != 0) {
                    func_080C95C0(counter_index, remaining);
                    record->unknown_02[0] = 15 - (14 * remaining) /
                                           (definition[2] | (definition[3] << 8));
                } else {
                    record->flags &= ~0x0A;
                    func_080C9574(0x59F, 0);
                    func_080C9574(0x581 + index, 1);
                    record->unknown_02[0] = 0;
                    *output++ = index + 1;
                    appended++;
                }
            } else if (record->flags & 2) {
                if (func_080C95A8(counter_index) == 0) {
                    s16 roll = (s16)func_08002804() % 100;

                    if (roll < 100 - definition[7 + snapshot_count]) {
                        record->flags |= 8;
                        record->unknown_02[0] = 1;
                        func_080C95C0(counter_index, definition[2]);
                        *output++ = index - 0x7F;
                        appended++;
                    } else {
                        u8 amount = definition[1];

                        amount += (s16)func_08002804() % (amount >> 1);
                        if (amount == 0)
                            amount = 1;
                        func_080C95C0(counter_index, amount);
                    }
                } else {
                    func_080C95C0(counter_index,
                                 (u8)(func_080C95A8(counter_index) - 1));
                }
            }
        }
    }
    return appended;
}
