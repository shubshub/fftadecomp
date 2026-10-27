#include "ffta.h"

struct ItemValue
{
    u8 unknown_000[4];
    u16 base;
    u16 minimum;
    u8 unknown_008[4];
    u8 flags;
    u8 unknown_00D[19];
};

extern const struct ItemValue g_table_0851D180[];
extern const u8 data_08527E62[][10];
extern u8 g_state_02000000[];
extern u8 func_080CC958(u8 category, u16 item);

/* Target [0x080CBC14, 0x080CBC92): 126 bytes, 52 instructions. */
u32 func_080CBC14(u8 category, u16 item)
{
    const struct ItemValue *entry = &g_table_0851D180[item];
    u32 value;

    if (entry->flags & 8)
    {
        u8 reduction = data_08527E62[g_state_02000000[0x21B4]][8];

        if (func_080CC958(category, item))
            reduction += 10;

        value = entry->base * (100 - reduction) / 100;
        if (value < entry->minimum)
            value = entry->minimum;
    }
    else
        value = entry->base;

    if (value == 0)
        value = 1;
    return value;
}
