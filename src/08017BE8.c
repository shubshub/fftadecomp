/* 0x08017BE8 - 10 bytes of code (0x08017BE8 .. 0x08017BF2).
 *
 * The index span in config/functions.json stops at 0x08017BF2, which is the
 * real end of the function: the last instruction is the Thumb `bx lr` at
 * 0x08017BF0, the two bytes at 0x08017BF2 are inter-function alignment
 * padding and 0x08017BF4 is the next prologue (`push {lr}`).  There is no
 * literal pool.
 *
 * target  008b 0138 0004 0014 7047
 *
 * It reads the halfword at +0x18 of the record and returns that count minus
 * one, sign-extended to 16 bits.
 *
 * The shape is forced by the instruction order:
 *
 *   - `ldrh` says the field at +0x18 is a u16.  A signed field would need a
 *     sign-extending load, and this compiler has no `ldrsh` with a
 *     displacement, so a s16 member would show the widening right after the
 *     load - before the subtraction, not after it.
 *   - `subs r0, #1` before the widening says the subtraction happens in 32
 *     bits and the narrowing is the return conversion, so the return type is
 *     s16 (`lsrs #24` would say u16).
 *
 * The record is the same one the sibling 0x08017E28 reaches through its
 * +0x04 pointer, so the type is the one declared there.
 */

#include "ffta.h"

typedef struct {
    u8  unknown_00[0x18];
    u16 field_18;
} Unit08017BE8;

s16 func_08017BE8(Unit08017BE8 *unit) {
    return unit->field_18 - 1;
}
