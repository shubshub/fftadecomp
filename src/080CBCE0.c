#include "ffta.h"

/* Complete [0x080CBCE0, 0x080CBD34): 84 bytes, 39 instructions, including
 * the literal pool.
 * f0b500210a4f4b00d81900884d1c002815d12806020e042a11d8054c1b190026
 * 500000190188002904d01980068006e0301f0002501c0006020e042af0d92806
 * 010e0429dfd900f051fd0006000ef0bc02bc0847
 *
 * Compacts the five-entry halfword table at 0x02001F30 the way
 * func_080CC2B4 compacts the 20-entry table at 0x02001F3C: each zero slot
 * takes the first non-zero entry after it, and that entry is cleared.  It
 * then returns func_080CC7CC's count of the non-zero entries, narrowed to a
 * byte.
 *
 * The slot address is taken at the top of the inner loop body, as in
 * func_080CC2B4: the ROM forms it in the inner loop's preheader from the
 * inner loop's own load of the table address (r4), not from the outer one
 * (r7).  Indexing the slot inside the `if` reuses the outer base instead and
 * compiles to 88 bytes.
 */
extern u16 data_02001F30[];
extern u32 func_080CC7CC(void);

u8 func_080CBCE0(void)
{
    u8 index;
    u8 next;

    for (index = 0; index < 5; index++) {
        if (data_02001F30[index] == 0) {
            for (next = index + 1; next < 5; next++) {
                u16 *slot = &data_02001F30[index];

                if (data_02001F30[next] != 0) {
                    *slot = data_02001F30[next];
                    data_02001F30[next] = 0;
                    break;
                }
            }
        }
    }
    return func_080CC7CC();
}
