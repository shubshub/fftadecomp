#include "ffta.h"

extern const u16 data_08393D2A[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08142B28(u32 value, u32 divisor);
extern s32 func_081426B8(s32 numerator, s32 denominator);

/* An inlined copy of func_08089834 (src/08089834.c), which ends at 0x080898DE
 * just before this function: 0x08089924..0x0808999A repeats its
 * 0x0808985C..0x080898CE mnemonic for mnemonic, apart from two reloads of
 * digits (0x0808993A, 0x08089944).  The remainder and quotient are the
 * calls to func_08142B28 and func_081426B8 that both make, as src/080899AC.c
 * writes them. */
static inline void inlined_08089834(u16 *output, u16 style, u16 number,
                                    u16 digits, u16 leading_zeroes,
                                    u16 tile_base)
{
    u16 *destination = output;
    u16 digit_base = 40;
    u16 leading;
    const u16 *place;
    u16 i;

    if (style == 0)
        digit_base = 30;
    leading = leading_zeroes == 1 ? digit_base : 0;
    place = &data_08393D2A[digits];

    for (i = 0; i < digits - 1; i++, place--) {
        u16 digit = func_08142B28(number, place[0]);
        digit = func_081426B8(digit, place[3]);
        if (digit != 0) {
            *destination++ = digit + digit_base + tile_base;
            leading = digit_base;
        } else {
            *destination++ = leading + tile_base;
        }
    }
    *destination = func_08142B28(number, 10) + digit_base + tile_base;
}

/* Complete 080898E0..080899AA: 202 bytes, 95 instructions (bl counted once). */
void func_080898E0(u32 window, s32 x, s32 y, u16 style, u16 number,
                   u16 digits, u16 leading_zeroes, u16 palette)
{
    inlined_08089834(func_0808B8E4(window, 1, x, y), style, number, digits,
                     leading_zeroes, palette << 12);
}
