/* func_08007138 - 0x08007138, 54 bytes (0x08007138 .. 0x0800716E)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  00b5021c002901d1002012e003200840002803d0042040420840011d8903090c
 *          101cfff7b1fe0021002801d0011c0c31081c02bc0847
 *
 * The heap allocator of the game.  It rounds the caller's byte count up to a
 * multiple of four, converts it to the unit count the heap works in and asks
 * func_08006EC0 for a block; the caller gets the payload, twelve bytes past
 * the header the heap wrote, and NULL when the heap had no room.
 *
 *   0x08007138  push {lr}
 *   0x0800713A  adds r2, r0, #0        owner, kept in r2 because r0 takes the
 *                                       masks below
 *   0x0800713C  cmp r1, #0 / bne        an empty request is refused
 *   0x08007144  movs r0, #3 / ands r0, r1
 *               cmp r0, #0 / beq        is the count a multiple of four?
 *   0x0800714C  movs r0, #4 / rsbs r0, r0, #0 / ands r0, r1
 *               adds r1, r0, #4        count = (count & ~3) + 4
 *   0x08007154  lsls r1, r1, #0xe / lsrs r1, r1, #0x10
 *                                       count >> 2, narrowed to sixteen bits
 *   0x08007158  adds r0, r2, #0 / bl 0x08006EC0
 *   0x0800715E  movs r1, #0 / cmp r0, #0 / beq
 *   0x08007164  adds r1, r0, #0 / adds r1, #0xc
 *                                       payload = block + 12
 *   0x0800716A  pop {r1} / bx r1       the non-void interworking return
 *
 * The unit count is a sixteen-bit value: func_08006EC0 keeps the block size
 * as a sixteen-bit unit count (it subtracts the request from the free size at
 * +6/+7 and finds the next block at `size << 2`), and the count passed here
 * is the number of four-byte units, so `lsls #14 / lsrs #16` is the sixteen
 * bit narrowing of `count >> 2` that gcc folds into the shift itself.
 *
 * The count is a u32 and not a u16: the callers copy it into r1 without a
 * mask, and a u16 parameter would make them narrow it first.
 */

#include "ffta.h"

void *func_08006EC0(void *owner, u16 units);

void *func_08007138(void *owner, u32 bytes)
{
    u16 units;
    void *block;

    if (bytes == 0)
        return 0;
    if (bytes & 3)
        bytes = (bytes & ~3) + 4;
    units = bytes >> 2;
    block = func_08006EC0(owner, units);
    return block ? (u8 *)block + 12 : 0;
}
