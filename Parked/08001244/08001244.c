// func_08001244: 0x08001244-0x080012BC, 120 bytes, 46 instructions
// (including the seven-word literal pool at 0x080012A0).
#include "ffta.h"

typedef unsigned long long u64;

extern u8 data_03002F58;
extern u64 data_03002F68[][32];
extern s32 data_03002F60[];
extern u64 data_03003170[][16];
extern s32 data_03003168[];

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
