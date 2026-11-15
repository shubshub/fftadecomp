#include "ffta.h"

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_flags_low : 2;
    u8 status : 3;
    u8 unknown_flags_high : 3;
    u8 unknown_03;
    u8 unknown_04[12];
} __attribute__((packed)) Item;

/* One 0x46-byte row.  The halfword at 0x41 is declared as src/080D2D54.c
 * declares it; this function reads it and tests bit 2. */
typedef struct {
    u8 unknown_00[0x41];
    u16 flags;
    u8 unknown_43[3];
} __attribute__((packed)) ItemMetadata;

extern const ItemMetadata g_table_0855AE4C[];

/* Complete [0x080D2E78, 0x080D2EB2): 58 bytes, 27 instructions, one-word pool.
 * 00b50278407803210840000210434621484307494018011c4131097842300078
 * 0002084304210840002803d1002002e04cae5508012002bc0847
 */
s32 func_080D2E78(Item *item)
{
    const ItemMetadata *metadata = &g_table_0855AE4C[item->id];

    if ((metadata->flags & 4) != 0)
        return 1;
    return 0;
}
