#include "ffta.h"

/* Complete target [0x080178A4, 0x0801799C), 248 bytes:
 * f0b557464e464546e0b481b0061c707d80460c062416708b00194004000cf17d49002bf1
 * 43f80004000c414641434900f26855186400b17f61434900b26857188246002100914046
 * 400080462849894640464208274b281c391c1a4029f1b4ff3368002b14d0706851464a1c
 * 1204120c924649082af19afc00062a8849461140000b014339806a884946114001437980
 * 318a04200840002814d04146cb191c1f4a19101f018848460840d021090208432080023b
 * 023a118848460840d021090208431880707d40002d18b07f40003f18009801300004000c
 * 00900128b8d901b038bc9846a146aa46f0bc01bc00470000ff0f0000ffff1f00
 *
 * Copies two tile rows of a scrolling window (same record as 0x08085558 and
 * 0x08017B9C): the source row is (field_1A + offset) * 2 wrapped by
 * field_17 * 2 through __modsi3, the destination row is offset * 2.  Each row
 * is a 16-bit CpuSet of `width` halfwords; an optional callback at +0 picks a
 * palette for the row (called through _call_via_r3) and flag 4 rewrites the
 * last two tiles with palette 0xD.
 */
typedef u8 (*RowPalette080178A4)(void *context, u16 row);

typedef struct {
    RowPalette080178A4 palette;
    void *context;
    u16 *destination;
    u16 *source;
    u16 flags;
    u8 unknown_12[3];
    u8 width;
    u8 unknown_16;
    u8 rows;
    u8 unknown_18[2];
    u16 scroll;
    u8 unknown_1C[2];
    u8 stride;
} TileWindow080178A4;

extern s32 func_08142950(s32 numerator, s32 denominator);
extern void func_0814186C(const void *source, void *destination, u32 count);

void func_080178A4(TileWindow080178A4 *window, s8 offset)
{
    u8 width = window->width;
    int row = offset;
    u16 first = func_08142950((u16)((window->scroll + row) * 2), window->rows * 2);
    u16 *source = window->source + width * first;
    u16 *destination = window->destination + (row << 1) * window->stride;
    u16 line = first;
    u16 i;

    for (i = 0; i < 2; i++) {
        func_0814186C(source, destination, ((u32)(width * sizeof(u16)) >> 1) & 0x001FFFFF);
        if (window->palette) {
            u8 palette = window->palette(window->context, line++ >> 1);
            destination[0] = (source[0] & 0xFFF) | (palette << 12);
            destination[1] = (source[1] & 0xFFF) | (palette << 12);
        }
        if (window->flags & 4) {
            destination[width - 2] = (source[width - 2] & 0xFFF) | 0xD000;
            destination[width - 1] = (source[width - 1] & 0xFFF) | 0xD000;
        }
        source += window->width;
        destination += window->stride;
    }
}
