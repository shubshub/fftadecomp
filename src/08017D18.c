/* func_08017D18 - 0x08017D18, 154 bytes of code
 *
 * The function index in config/functions.json stops at 0x08017D3A (34 bytes,
 * mid-`bl`-argument); the real body runs to the Thumb interworking epilogue
 * `pop {r4,r5,r6}; pop {r0}; bx r0` at 0x08017DAC..0x08017DB0, and 0x08017DB4
 * is the next prologue.  There is no literal pool: nothing is `ldr [pc]`, and
 * the two bytes at 0x08017DB2 are inter-function alignment padding, not code.
 *
 * Semantics: it overwrites the flag byte at +0x10 with the argument, then
 * reacts to what that clears.
 *
 *   - `a` (old & 6) and `b` (old & 8) are the two bits the store may drop.
 *   - a bit that the new value does not carry means the object is being torn
 *     down, so the body only runs when (a & mask) == 0 and there is an owner.
 *   - the flag bit 1 path re-asserts bit 2/3 on the way out.
 *
 * Layout notes, all of them forced by the immediate offsets:
 *   +0x04 owner pointer (only +0x14 of the pointee is read here; 0x08017BF4
 *        also reads +0x13 and +0x15, and tests its own +0x10 against 8)
 *   +0x08/+0x0A/+0x0C are halfwords - `strh` at +0x08 and +0x0C
 *   +0x0E is a halfword nothing in this function touches; it has to exist or
 *        the flag byte slides to +0x0E.  0x08017AC4 treats +0x10 as a halfword,
 *        so the two bytes are one field seen at two widths.
 *
 * The `lsls #24 / lsrs #24` pair after `8 & old` is the u8 narrowing of `b`;
 * `a` is used only in further `&`s so it needs no mask.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u8 value_14;
} Owner08017D18;

typedef struct {
    u32 unknown_00;
    Owner08017D18 *owner;
    u16 field_08;
    u16 field_0a;
    u16 field_0c;
    u16 unknown_0e;
    u8 field_10;
    u8 unknown_11;
    u8 field_12;
} State08017D18;

/* 0x08017BF4 - reads the owner's +0x13 and +0x15 and this object's own flag
 * byte, returns a u16; matched here only as a call. */
u16 func_08017BF4(State08017D18 *s);

void func_08017D18(State08017D18 *s, u8 mask) {
    u8 a = s->field_10 & 6;
    u8 b = s->field_10 & 8;

    s->field_10 = mask;

    if (!(a & mask)) {
        if (s->owner != 0) {
            if (mask & 1) {
                if (b & 8) {
                    s->field_10 = mask | 8;
                }
            }
            if ((a & 4) || (mask & 4)) {
                s->field_12 = 0;
                s->field_0c = 0;
            } else {
                s->field_08 = func_08017BF4(s) + 8;
                s->field_0a = (s->owner->value_14 << 3) + 4;
                s->field_12 = 0x11;
            }
        }
    }

    if (s->field_10 & 1) {
        if (a & 4) {
            s->field_10 |= 4;
        }
        if (b) {
            s->field_10 |= 8;
        }
    }
}