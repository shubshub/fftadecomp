#include "ffta.h"

struct ItemInfo
{
    u8 unknown_00[4];
    u16 base;
    u16 minimum;
    u8 unknown_08[4];
    u8 flags;
    u8 unknown_0D[0x13];
};

extern const struct ItemInfo g_table_0851D180[];
extern const u8 data_08527E62[][10];
extern u8 g_state_02000000[];
extern u8 func_080CC958(u8 category, u16 item);

/* Complete target: [0x080CBC14, 0x080CBC92), 126 bytes, 52 instructions.
 * 70b50006060e09040b0c154958014518297b0820084000282ad0124a1248134940180178880040184000083280180478301c
 * 191c00f086fe0006002803d0201c0a300006040ea8886421091b4843642176f028fde98888420bd2081c09e0000080d15108
 * 627e520800000002b4210000a888002800d1012070bc02bc0847
 */
u32 func_080CBC14(u8 category, u16 item)
{
    u32 value;

    if (g_table_0851D180[item].flags & 8)
    {
        u8 reduction = data_08527E62[g_state_02000000[0x21B4]][8];

        if (func_080CC958(category, item))
            reduction += 10;

        value = g_table_0851D180[item].base * (100 - reduction) / 100;
        if (value < g_table_0851D180[item].minimum)
            value = g_table_0851D180[item].minimum;
    }
    else
        value = g_table_0851D180[item].base;

    if (value == 0)
        value = 1;
    return value;
}
