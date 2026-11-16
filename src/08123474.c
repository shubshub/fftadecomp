#include "ffta.h"

/* Complete [0x08123474, 0x081234B4): 64 bytes, 31 instructions, no literal
 * pool.
 * 70b581b00d1c6978ac780a062606a14210d00f20031c0b40110f021c2240340f934201d0
 * a14205d1e8780090181c231c01f066fa8820400001b070bc02bc0847
 *
 * Script bytes 1 and 2 are packed grid positions (x = pos % 16,
 * y = pos / 16).  Two distinct positions that share a row or a column are
 * passed to func_08124974 with script byte 3 as its selector. */

void func_08124974(u8 start_x, u8 start_y, u8 end_x, u8 end_y, u8 selector);

u32 func_08123474(void *context, const u8 *script)
{
    u8 start_x;
    u8 start_y;
    u8 end_x;
    u8 end_y;
    u32 start = script[1];
    u32 end = script[2];

    /* The u8 narrowing is in the ROM: lsls #24 of both bytes at
     * 0x0812347E/0x08123480, ahead of the beq at 0x08123484 (the cmp
     * itself uses the unshifted bytes). */
    if ((u8)start == (u8)end)
        return 0x110;

    start_x = start % 16;
    /* The high nibbles are lsrs #28 of those narrowed bytes at
     * 0x0812348C/0x08123492, not lsrs #4. */
    start_y = (u8)start / 16;
    end_x = end % 16;
    end_y = (u8)end / 16;

    if (start_x == end_x || start_y == end_y)
        func_08124974(start_x, start_y, end_x, end_y, script[3]);
    return 0x110;
}
