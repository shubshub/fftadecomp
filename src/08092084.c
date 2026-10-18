/* func_08092084 - 0x08092084, 22 bytes
 *
 * Two bytes into a table at a signed 16-bit index.  Three details have to be
 * right, and each of them is visible in the instructions:
 *
 *   - `base++` between the two stores.  It is an in-place pointer increment,
 *     not a folded addressing mode, and it is what keeps the base live across
 *     the first store - which is in turn what makes the frame appear at all.
 *   - `u32 off = index * 2;` as a *variable*.  agbcc emits the two-operand add
 *     base-first only when the offset is held in a variable; inlined into the
 *     address expression it comes out index-first, and the ROM is base-first.
 *   - an arithmetic shift, so the index is signed: (index << 16) >> 15 is
 *     index * 2 for a signed 16-bit type and something else for unsigned.
 *
 *   target  10b5 0904 c913 4418 2270 0130 4018 0370 10bc 01bc 0847
 */

#include "ffta.h"

void func_08092084(u8 *base, s16 index, u8 lo, u8 hi) {
    u32 off = index * 2;
    base[off] = lo;
    base++;
    base[off] = hi;
}