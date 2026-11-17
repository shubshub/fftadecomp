/* func_08001244: 0x08001244-0x080012BC, 120 bytes, 46 instructions
 * (including the seven-word literal pool at 0x080012A0).
 * Target: f0b5164c207803021549164a800080185b180068261c171c134c144d002805dd
 *         1349144a06c301380028fbdc3078c101800040190b190068002805dd0c490d4a
 *         06c301380028fbdc30788000c2194019002101601160f0bc01bc0047
 *         582f0003682f0003602f00037031000368310003a800f80000000000
 */
#include "ffta.h"

typedef unsigned long long u64;

extern u8 data_03002F58;
extern u64 data_03002F68[][32];
extern s32 data_03002F60[];
extern u64 data_03003170[][16];
extern s32 data_03003168[];

/* The same helper as src/08001194.c, character for character. */
static inline void HideEntries(u64 *entry, s32 count)
{
    for (; count > 0; count--)
        *entry++ = 0x00F800A8;
}

void func_08001244(void)
{
    HideEntries(data_03002F68[data_03002F58], data_03002F60[data_03002F58]);
    HideEntries(data_03003170[data_03002F58], data_03003168[data_03002F58]);

    data_03002F60[data_03002F58] = data_03003168[data_03002F58] = 0;
}
