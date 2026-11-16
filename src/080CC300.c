#include "ffta.h"

/* Complete [0x080CC300, 0x080CC348): 72 bytes, 34 instructions, one literal word.
 * f0b50021094fc81900784d1c002814d12806000e132810d8044c0b1900260219
 * 1178002904d01970167006e0642e000201300006000e1328f1d92806010e1329
 * e1d9f0bc01bc0047
 *
 * Compacts the 20-entry byte list at 0x02002E64 the way func_080CC2B4
 * compacts its halfword table: each zero slot takes the first non-zero
 * entry after it, and that entry is cleared.  func_080CCA54 counts the
 * non-zero entries of the same list.
 *
 * The list is a member of the state block at 0x02000000, as
 * func_0805262C reads it (g_state_02000000.values[item]); it ends where
 * the 16-byte records at 0x2E78 begin (func_080CCBC4).  The literal word
 * is g_state_02000000 + 0x2E64.  Read through a separate data_02002E64
 * symbol instead, the inner loop copies the outer loop's base register
 * where the ROM reloads the literal (62/72 bytes).
 */
typedef struct {
    u8 unknown_0000[0x2E64];
    u8 values[20];
} ValueState;

extern ValueState g_state_02000000;

void func_080CC300(void)
{
    u8 index;
    u8 next;

    for (index = 0; index < 20; index++) {
        if (g_state_02000000.values[index] == 0) {
            for (next = index + 1; next < 20; next++) {
                if (g_state_02000000.values[next] != 0) {
                    g_state_02000000.values[index] = g_state_02000000.values[next];
                    g_state_02000000.values[next] = 0;
                    break;
                }
            }
        }
    }
}
