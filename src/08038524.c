/* Target bytes (28):
 * 02 1c 09 04 03 48 89 0b 09 18 03 48 09 18 08 78
 * 0a 70 70 47 00 00 00 02 08 2b 00 00
 */
#include "ffta.h"

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

u8 func_08038524(u8 value, u16 index)
{
    u8 previous = g_state_02000000.entries[index].value;

    g_state_02000000.entries[index].value = value;
    return previous;
}
