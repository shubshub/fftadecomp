#include "ffta.h"

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

/* The object at 0x02002FC4 as src/08063060.c declares it.  The ROM reaches
   the list both as this base plus 0xC72 (0x0802D7C6) and through the folded
   literal 0x02003C34 (0x0802D7CC, 0x0802D7F0), which is this base plus 0xC70. */
typedef struct {
    u8 unknown_000[0xC6E];
    u8 total;
    u8 count;
    u16 entries[4];
} SelectionState;

extern SelectionState g_state_02002FC4;
extern BufferCopier data_0836D4BC[];
extern u8 func_0802D764(void);

/* Complete [0x0802D7A0, 0x0802D822): 130 bytes, 55 instructions.
 * Target: f0b557464e464546e0b4134dfff7daff0006000e804600282cd000240027474528da042082460d49491989460c4e3588002d19d101343a195046821a520009490b68301c494614f133fd5146081b40000349081805800be0c42f0002720c0000343c0002bcd4360802208144023601374745dcdb38bc9846a146aa46f0bc01bc0047
 */
void func_0802D7A0(void)
{
    SelectionState *selection = &g_state_02002FC4;
    s32 count = func_0802D764();
    s32 holes;
    s32 i;

    if (count == 0)
        return;

    holes = 0;
    i = 0;
    while (i < count) {
        if (selection->entries[i] == 0) {
            s32 next_holes = holes + 1;

            data_0836D4BC[0](&selection->entries[i], &selection->entries[i + 1],
                             (4 - (i + next_holes)) * sizeof(selection->entries[0]));
            selection->entries[4 - next_holes] = 0;
            holes = next_holes;
        } else {
            i++;
        }
    }
}
