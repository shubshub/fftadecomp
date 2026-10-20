#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 status;
    u8 unknown_03[9];
} ProgressRecord;

extern u8 g_state_02002CB4[];
extern const u8 g_table_085653F0[];

u32 func_08002804(void);
void func_080C95C0(u16 index, u32 value);
void func_080C9574(u16 bitIndex, u16 enabled);

void func_080CFA48(u8 index)
{
    ProgressRecord *record = (ProgressRecord *)g_state_02002CB4 + index;
    const u8 *definition = g_table_085653F0 + index * 38;
    u16 counterIndex = index + 20;
    u8 amount;
    s32 scan;

    record->flags = (record->flags & ~8) | 2;
    record->status = 0;
    amount = definition[1];
    amount += (s16)func_08002804() % (amount >> 1);
    if (amount == 0)
        amount = 1;
    func_080C95C0(counterIndex, amount);

    record = (ProgressRecord *)g_state_02002CB4 + 1;
    for (scan = 1; scan <= 30; scan++) {
        if ((record->flags & 3) != 3)
            return;
        record++;
    }
    func_080C9574(0x59F, 1);
}
