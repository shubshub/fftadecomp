#include "ffta.h"

/* Complete [0x080CC2B4, 0x080CC300): 76 bytes, 36 instructions.
 * f0b500210a4f4b00d81900884d1c002815d12806020e132a11d8054c1b190026
 * 500000190188002904d01980068006e03c1f0002501c0006020e132af0d92806
 * 010e1329dfd9f0bc01bc0047
 *
 * Compacts the 20-entry halfword table at 0x02001F3C: each zero slot takes
 * the first non-zero entry after it, and that entry is cleared.
 * func_080CB27C, one of six callers, runs this and then passes the non-zero
 * entries counted by func_080CCA80 to func_080028C8 with the halfword
 * comparator func_080CB63C.
 *
 * The slot address is taken at the top of the inner loop body: the ROM
 * forms it in the inner loop's preheader from the inner loop's own load of
 * the table address (r4), not from the outer one (r7).  Indexing the slot
 * inside the `if` reuses the outer base instead and compiles to 80 bytes.
 */
extern u16 data_02001F3C[20];

void func_080CC2B4(void)
{
    u8 index;
    u8 next;

    for (index = 0; index < 20; index++) {
        if (data_02001F3C[index] == 0) {
            for (next = index + 1; next < 20; next++) {
                u16 *slot = &data_02001F3C[index];

                if (data_02001F3C[next] != 0) {
                    *slot = data_02001F3C[next];
                    data_02001F3C[next] = 0;
                    break;
                }
            }
        }
    }
}
