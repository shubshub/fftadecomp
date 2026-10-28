#include "ffta.h"

struct Record080BC7AC {
    u8 unknown00[0x21];
    u8 flag;
    u8 unknown22[6];
};

extern const struct Record080BC7AC g_table_0854CD54[];

/* Complete [0x080BC7AC, 0x080BC7D2): 38 bytes, 17 instructions. */
s32 func_080BC7AC(u16 index)
{
    const struct Record080BC7AC *record = &g_table_0854CD54[index];

    if (record->flag != 0)
        return 1;
    return 0;
}
