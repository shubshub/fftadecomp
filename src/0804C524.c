/* func_0804C524 - 0x0804C524, 116 bytes
 *
 * Fills one 28-byte record of the table at `base`, the same shape as
 * func_0804C5F8 (0x0804C5F8) with three differences:
 *
 *   - it takes an eleventh argument, written to the byte at +0x12;
 *   - the byte at +0x0C is cleared instead of being set to 6;
 *   - because of those two the allocation shifts: the zero that feeds +0x08
 *     and +0x0C keeps a copy in r8 (`mov r8, r1`) and is reloaded into r4 for
 *     the halfword store (`mov r4, r8`), and the +0x18 word is re-read off the
 *     stack late (`ldr r1, [sp, #0x2c]`) rather than living in a callee-saved
 *     register across the body.  Both fall out of the source; neither is
 *     spelled deliberately.
 *
 * The destination stride is `index * 28`, written as shift/subtract/shift
 * (3 x 8 - x, then x4), and the compiler only emits it in that order when the
 * offset is computed before the base is added to it - hence
 * `index * 28 + (u32)base`.
 *
 * The sixth argument arrives as a 32-bit word and is narrowed to a byte before
 * it goes into the u16 field at +0x0A; the mask shows up as
 * `lsls r6, #24 / lsrs r6, #24`.  Narrowing in a local is what puts it between
 * the two halves of the selector's own mask, as the ROM has it.
 *
 * The selector is a u16 scaled by the 4-byte slot it picks, so agbcc emits the
 * truncation and the scale together as `lsls #16` then `lsrs #14` - the
 * `(u16)sel << 2` of `sel * 4`, not a `>> 14`.
 *
 * Incoming stack words sit at `frame_size + 4*(n-5)`, one word lower than
 * entry-SP arithmetic suggests.  `frame_size` is 32 here (five pushes plus the
 * three callee-saved registers), so `a5` is at `[sp, #0x20]` and the eleventh
 * argument at `[sp, #0x38]`.
 *
 * Argument order in the signature is not the store order; the stores below
 * follow the instructions.
 *
 * `ffta.h`'s `Entry` still spells +0x12 as `unknown_12`, which is what this
 * function shows it to be - the eleventh argument, a byte, written last.  It
 * is reached by an explicit offset here rather than by a member, because the
 * header is shared with work on the other fields; the two spellings compile
 * identically.
 */

#include "ffta.h"

void func_0804C524(Entry *base, u16 index, u32 selector,
                   u8 a4, u8 a5, u32 a6, u8 a7, u32 a8,
                   u8 *row, u16 a10, u8 a11)
{
    u16 sel = selector;
    u8 byte = (u8)a6;
    u8 *slot = row + sel * 4;
    u32 head = *(u32 *)slot;
    Entry *e = (Entry *)(index * 28 + (u32)base);

    e->field_0e = *(u16 *)(row + head);
    e->field_00 = (u32)(row + (head + 2));
    e->field_08 = 0;
    e->field_0f = 0;
    e->field_0d = 1;
    e->field_0a = byte;
    e->field_10 = a4;
    e->field_11 = a5;
    e->field_0c = 0;
    e->field_13 = a7;
    e->field_18 = a8;
    e->field_16 = a10;
    e->field_12 = a11;
}