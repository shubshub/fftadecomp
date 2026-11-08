#include "ffta.h"

extern u16 data_08393D2A[];
extern u16 *func_0808B8E4(u32 window, u32 layer, s32 x, s32 y);
extern u32 func_08142B28(u32, u32);
extern s32 func_081426B8(s32, s32);

static inline void DrawDigits(u32 address, u16 large, u16 value,
                              u16 digits, u16 alignment, u16 attributes)
{
    u16 *destination = (u16 *)address;
    u16 base;
    u16 blank;
    u16 *place;
    u16 index;
    u16 digit;

    base = 40;
    if (large == 0)
        base = 30;
    blank = alignment == 1 ? base : 0;
    place = data_08393D2A + digits;
    for (index = 0; index < digits - 1; ++index, --place) {
        digit = func_081426B8((u16)func_08142B28(value, place[0]), place[3]);
        if (digit != 0) {
            *destination++ = digit + base + attributes;
            blank = base;
        } else {
            *destination++ = blank + attributes;
        }
    }
    *destination = func_08142B28(value, 10) + base + attributes;
}

/* Complete 080898E0..080899AA: 202 bytes, 95 instructions (bl counted once). */
void func_080898E0(u32 window, s32 x, s32 y, u16 large, u16 value,
                   u16 digits, u16 alignment, u16 palette)
{
    DrawDigits((u32)func_0808B8E4(window, 1, x, y), large, value, digits,
               alignment, palette << 12);
}
