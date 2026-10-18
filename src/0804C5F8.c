/* func_0804C5F8 - 0x0804C5F8, 110 bytes
 *
 * Fills one 28-byte record of the table at `base`.  The destination stride is
 * `index * 28`, spelled shift/subtract/shift (3 x 8 - x, then x4), and the
 * compiler only emits it in that order when the offset is computed before the
 * base pointer is added to it - hence `index * 28 + (u32)base`.
 *
 * The sixth argument arrives as a 32-bit word and is narrowed to a byte before
 * it goes into the u16 field at +0x0A; the mask is visible as
 * `lsls r6, #24 / lsrs r6, #24`.  Doing the narrowing in a local is what puts
 * it between the two halves of the selector's own mask, as the ROM has it.
 *
 * The selector is a u16 scaled by the 4-byte slot it picks, so agbcc emits the
 * truncation and the scale together as `lsls #16` then `lsrs #14` - i.e. the
 * `(u16)x << 2` of `x * 4`, not a `>> 14`.  Written as `(u16)kind >> 14` it
 * collapses to a single `lsrs #30` instead.
 *
 * Argument order in the signature is not the store order; the stores below
 * follow the instructions.
 *
 * Types are declared here rather than pulled from ffta.h: the prototype in
 * ffta.h spells the sixth parameter `u8`, and agbcc only reproduces the ROM's
 * instruction order when it is a wider word narrowed in the body.
 */

#include "ffta.h"

void func_0804C5F8(Entry *base, u16 index, u32 selector,
                   u8 a4, u8 a5, u32 a6, u8 a7, u32 a8,
                   u8 *row, u16 a10)
{
    u16 sel = selector;
    u8 byte = (u8)a6;
    u8 *slot = row + sel * 4;
    u32 head = *(u32 *)slot;
    Entry *e = (Entry *)(index * 28 + (u32)base);

    e->field_0e = *(u16 *)(row + head);
    e->field_00 = (u32)(row + (head + 2));
    e->field_0f = 0;
    e->field_08 = 0;
    e->field_0d = 1;
    e->field_0a = byte;
    e->field_10 = a4;
    e->field_11 = a5;
    e->field_0c = 6;
    e->field_13 = a7;
    e->field_18 = a8;
    e->field_16 = a10;
}