#include "ffta.h"

extern const u8 g_table_08528984[];
extern u8 g_state_02002CB4[];

u32 func_080CE4DC(u16 index, u8 selector);

u32 func_080CEC78(u16 index, u8 slot, u8 entry)
{
    u32 base = func_080CE4DC(index, 0x36);
    const u8 *record;
    u8 flags;
    u8 low;
    u8 high;
    u32 factor;

    if (base == 0)
        return 0;

    record = g_table_08528984 + slot * 96;
    flags = g_state_02002CB4[slot * 12 + 1];
    if ((flags & 1) && (flags & 2))
        return base - base * record[0x41 + entry] / 100;

    low = record[0x40];
    high = record[0x41];
    factor = low | (high << 8);
    return base + base * factor / 100;
}
