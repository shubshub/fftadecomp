#include "ffta.h"

typedef struct {
    u8 unknown_00[0x312];
    u8 characters[10][2];
    u8 count;
} Text0812B184;

extern u32 func_08013A5C(u16 character);

/* Target: complete [0x0812B184, 0x0812B208), 132 bytes, 52 instructions. */
u16 func_0812B184(Text0812B184 *text)
{
    u16 index = 0;
    u16 width = 0;
    for (; index < text->count; index++) {
        if (text->characters[index][0] == 0x40 &&
            text->characters[index][1] == 0x73)
            width += 6;
        else
            width += func_08013A5C(((text->characters[index][0] << 8) |
                                   text->characters[index][1]) & 0x7fff);
    }
    return width;
}
