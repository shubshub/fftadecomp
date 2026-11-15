#include "ffta.h"

/* Complete [0x08038564, 0x080385A6): 66 bytes, 27 instructions, three literal
 * words in one pool.
 * 70b50004050c002306480024064a8118021c064e0878a8420ad10c709019048001200be0
 * 00000002082b00000a2b00000431043201333f2becdd002070bc02bc0847
 */

/* The 64-entry table of src/08038524.c and src/080385A8.c. */
typedef struct {
    u8 value;
    u8 unknown_01;
    u16 count;
} SlotEntry;

typedef struct {
    u8 unknown_00[0x2B08];
    SlotEntry entries[64];
} EntryState;

extern EntryState g_state_02000000;

s32 func_08038564(u16 value)
{
    s32 index;

    for (index = 0; index < 64; index++) {
        if (g_state_02000000.entries[index].value == value) {
            g_state_02000000.entries[index].value = 0;
            g_state_02000000.entries[index].count = 0;
            return 1;
        }
    }
    return 0;
}
