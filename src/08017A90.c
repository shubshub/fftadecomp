/* func_08017A90 - 0x08017A90, 50 bytes.
 *
 * config/functions.json and symbols/functions.txt record only 12 bytes here;
 * the body actually runs to 0x08017AC0, and the two bytes of 0x0000 at
 * 0x08017AC2 are inter-function filler (0x08017AC4, see src/08017AC4.c, is the
 * next function - same shape as 0x08017424, whose 0x0000 at 0x0801748E sits
 * outside its 106-byte symbol too).  No literal pool: every operand is either
 * an immediate or a short constant materialised into a scratch register.
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   00b5 021c 0904 090c 4029 0bd0 8029 0dd1 1a21 505e 937d c018 1823
 *   d15e 505e 8842 05db 0020 04e0 1a21 505e 0028 f9d0 0120 02bc 0847
 *
 * A predicate over the same 0x1A halfword the callers read with ldrh: for
 * every kind but two it answers 1.  Kind 0x40 asks whether field_1A is zero;
 * kind 0x80 asks whether field_1A + field_16 has yet to reach field_18.  The
 * halfword argument is truncated to u16 on entry (`lsls #16` / `lsrs #16`),
 * and the s16 loads plus `blt` make the sum a signed comparison.
 *
 * The shared `return 1` is written as a label rather than three separate
 * returns because the ROM has one `movs r0, #1` block at 0x08017ABC, with the
 * 0x80 rejections branching to it and the 0x40 path falling into it - and it
 * sits immediately before the `pop {r1}; bx r1` epilogue.  Written as three
 * plain returns, agbcc sinks the `movs r0, #0` block to the end of the
 * function instead and the two tails swap places.
 */
#include "ffta.h"

typedef struct {
    u8  unknown_00[0x16];
    u8  field_16;
    u8  unknown_17;
    s16 field_18;
    s16 field_1A;
} Rec08017A90;

u8 func_08017A90(Rec08017A90 *rec, u16 kind) {
    if (kind != 0x40) {
        if (kind != 0x80)
            goto one;
        if (rec->field_1A + rec->field_16 < rec->field_18)
            goto one;
        return 0;
    }
    if (rec->field_1A == 0)
        return 0;
one:
    return 1;
}