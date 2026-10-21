/* func_08017C28 - 0x08017C28, 64 bytes of code.
 *
 * The index span in config/functions.json stops at 0x08017C68, which is the
 * real end of the function: the interworking epilogue `pop {r4}; pop {r0};
 * bx r0` sits at 0x08017C62..0x08017C66 and 0x08017C68 is the next prologue
 * (`push {r4, r5, lr}`).  There is no literal pool.
 *
 * target  10b5 041c 1b06 1b0e 2260 6160 0022 6274 181c 002b 00d1 0320
 *         2074 a274 e281 a281 6281 2281 0029 08d0 201c fff7cfff 2081 6068
 *         007d c000 0430 6081 10bc 01bc 0047
 *
 * The record is the one the sibling functions use: 0x08017BF4 reads +0x04,
 * +0x10 and the owner's +0x13/+0x15, 0x08017C68 and 0x08017D18 use +0x08,
 * +0x0A, +0x0C, +0x10, +0x11 and +0x12.  So this is the same struct as
 * src/08017D18.c, seen here from its other side.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u8 value_14;
} Owner08017C28;

typedef struct {
    u32 unknown_00;
    Owner08017C28 *owner;
    u16 field_08;
    u16 field_0a;
    u16 field_0c;
    u16 unknown_0e;
    u8 field_10;
    u8 unknown_11;
    u8 field_12;
} State08017C28;

/* 0x08017BF4 - reads the owner's +0x13 and +0x15 and this object's own flag
 * byte, returns a u16; matched here only as a call. */
u16 func_08017BF4(State08017C28 *s);

void func_08017C28(State08017C28 *s, Owner08017C28 *owner, u32 value, u8 flags) {
    s->unknown_00 = value;
    s->owner = owner;
    s->unknown_11 = 0;
    s->field_10 = flags ? flags : 3;
    s->field_12 = 0;
    s->unknown_0e = 0;
    s->field_0c = 0;
    s->field_0a = 0;
    s->field_08 = 0;

    if (owner != 0) {
        s->field_08 = func_08017BF4(s);
        s->field_0a = (s->owner->value_14 << 3) + 4;
    }
}
