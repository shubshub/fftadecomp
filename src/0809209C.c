/* func_0809209C - 0x0809209C, 32 bytes
 *
 * Reads one byte out of a table at a *constant* offset and hands it, together
 * with the table pointer itself, to the list-insert helper at 0x08000D48.
 * Three details have to be right:
 *
 *   - the offset is a constant, 324, and 324 does not fit in a Thumb `movs`
 *     immediate.  agbcc materialises it as 0xa2 << 1 rather than reaching for
 *     a literal pool, which is why the pair `movs r2, #0xa2 / lsls r2, r2, #1`
 *     is in the ROM at all.
 *   - `adds r1, r0, #0` at the top.  The incoming pointer is live across the
 *     byte load (it is the second argument to the call), and the load itself
 *     wants r0, so the pointer is copied out first.  The same variable being
 *     read twice is what forces the copy.
 *   - the two constants go through the pool, one entry each, in argument
 *     order, and the pool lands immediately after the `pop {r0}; bx r0`
 *     interworking epilogue - 24 bytes of code, so it is already aligned.
 *
 *   target  00b5 011c a222 5200 8818 0078 024a 034b 6ef74cfe 01bc 0047
 *           52000004 01004020
 */

#include "ffta.h"

/* 0x08000D48 - takes the byte as an index into a u16 table, then writes the
 * remaining three words into a 16-byte record; not further identified. */
void func_08000D48(u8 index, void *record, u32 a, u32 b);

void func_0809209C(u8 *base) {
    func_08000D48(base[324], base, 0x04000052, 0x20400001);
}