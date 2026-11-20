#include "ffta.h"

extern void func_08002FB8(s16 value, u8 *text);
extern u32 func_081444B8(const void *text);

u16 func_080142DC(void *destination, u32 number, u32 field_width)
{
    u16 value = number;
    u8 width = field_width;
    u8 text[8];
    u8 *digits;
    u8 *out;
    s32 length;
    s32 remaining;
    s32 i;
    s32 digit;
    u16 written;
    u16 glyph;

    if (width == 0)
        width = 1;
    func_08002FB8(value, text);
    digits = text;
    length = func_081444B8(text);
    remaining = 0;
    for (i = 0; i < length; i++, digits++) {
        if (*digits != ' ') {
            remaining = length - i;
            break;
        }
    }
    out = destination;
    written = 0;
    digit = 0;
    for (i = 0; i < width; i++) {
        if (width > remaining) {
            *out++ = 0x81;
            *out++ = 0x18;
            written += 2;
            remaining++;
        } else {
            glyph = (digits[digit] + 0xE8) | (s16)0x8000;
            digit++;
            *out++ = glyph >> 8;
            *out++ = glyph;
            written += 2;
        }
    }
    *out = 0;
    written++;
    return written;
}
