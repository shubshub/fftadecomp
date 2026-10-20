/* 0x08017B9C - 76 bytes (the index span of 20 is truncated: it cuts the function
 * off mid-branch at 0x08017BB0, just after `bge`.  The code runs on to the
 * interworking epilogue `pop {r4}; pop {r1}; bx r1` at 0x08017BE6, and the
 * next function starts at 0x08017BF4.  There is no literal pool - the `bl` is
 * a direct 32-bit Thumb BL, so func_08142950 is a real call, not a pool word).
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  10b5 041c 0906 0916 608b 0918 0904 0a14 002a 01da 0020 08e0
 *           1823 e05e 0138 8242 02dd 208b 0138 00e0 080c 0004 000c e17d
 *           2af1c0fe 0004 000c 617d 4900 4843 a48b 0019 0004 000c 10bc
 *           02bc 0847
 *
 * The first half is the clamp of 0x08017B68 verbatim - (s8)index + field_1A
 * squeezed into [0, field_18 - 1] - with the result feeding a call instead of
 * being returned: func_08142950(base, field_17), doubled by field_15, offset
 * by field_1C and truncated back to u16.
 *
 * `base` is held wide and narrowed on the way out.  That is not decoration: it
 * is what puts the u16 conversion of field_18 - 1 at the join rather than in
 * its own branch, which is where the ROM has it.
 *
 * The caller-side `<< 1` is likewise load-bearing: written as `* 2` the
 * compiler reassociates the chain and folds the halving into the call result.
 */

#include "ffta.h"

typedef struct {
    u8  unknown_00[0x15];
    u8  field_15;
    u8  unknown_16;
    u8  field_17;
    u16 field_18;
    u16 field_1A;
    u16 field_1C;
} ClampState08017B9C;

s32 func_08142950(s32 numerator, s32 denominator);

u16 func_08017B9C(ClampState08017B9C *state, u32 index) {
    s16 value = (s8)index + state->field_1A;
    u32 base;

    if (value < 0)
        base = 0;
    else if (value > (s16)state->field_18 - 1)
        base = state->field_18 - 1;
    else
        base = (u16)value;

    return (u16)func_08142950((u16)base, state->field_17) * (state->field_15 << 1) + state->field_1C;
}
