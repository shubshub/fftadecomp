/* Complete target [0x080178A4, 0x0801799C), 248 bytes, 116 instructions
 * (literal pool 0x00000FFF, 0x001FFFFF at 0x08017994):
 * f0b557464e464546e0b481b0061c707d80460c062416708b00194004000cf17d49002bf1
 * 43f80004000c414641434900f26855186400b17f61434900b26857188246002100914046
 * 400080462849894640464208274b281c391c1a4029f1b4ff3368002b14d0706851464a1c
 * 1204120c924649082af19afc00062a8849461140000b014339806a884946114001437980
 * 318a04200840002814d04146cb191c1f4a19101f018848460840d021090208432080023b
 * 023a118848460840d021090208431880707d40002d18b07f40003f18009801300004000c
 * 00900128b8d901b038bc9846a146aa46f0bc01bc00470000ff0f0000ffff1f00
 *
 * Copies two tile rows of a scrolling region out to the destination; the
 * record is the one 0x0801799C recolours (and 0x08085558 / 0x08017B9C read).
 * The source row is (field_1A + row) * 2 wrapped by rows * 2 through
 * func_08142950 (signed remainder); the destination row is row * 2.  Each row
 * is a 16-bit CpuSet (func_0814186C) of `stride` halfwords.  An optional
 * callback at +0 picks a palette for the row (called through _call_via_r3),
 * and flags & 4 gives the last two entries palette 0xD.
 */

#include "ffta.h"

typedef u8 (*RowPalette080178A4)(void *context, u16 line);

typedef struct {
    RowPalette080178A4 row_palette;
    void *context;
    u16 *destination;
    u16 *tiles;
    u16  flags;
    u8   unknown_12[0x03];
    u8   stride;
    u8   unknown_16;
    u8   rows;
    u8   unknown_18[0x02];
    u16  field_1A;
    u8   unknown_1C[0x02];
    u8   field_1E;
} State080178A4;

s32 func_08142950(s32 numerator, s32 denominator);
void func_0814186C(const void *source, void *destination, u32 control);

void func_080178A4(State080178A4 *state, s8 row)
{
    u8 stride = state->stride;
    u16 first = func_08142950((u16)((state->field_1A + row) << 1), state->rows << 1);
    u16 *row_tiles = state->tiles + stride * first;
    u16 *copy = state->destination + (row << 1) * state->field_1E;
    /* The ROM keeps the remainder twice: r0 scales the source row
     * (0x080178D0) and sl, set at 0x080178E4, is the callback's row counter,
     * advanced at 0x0801790E only when the callback is present. */
    u16 line = first;
    u16 i;

    for (i = 0; i < 2; i++) {
        func_0814186C(row_tiles, copy, ((stride * sizeof(u16)) >> 1) & 0x1FFFFF);
        if (state->row_palette) {
            u8 palette = state->row_palette(state->context, line++ >> 1);
            copy[0] = (row_tiles[0] & 0xFFF) | (palette << 12);
            copy[1] = (row_tiles[1] & 0xFFF) | (palette << 12);
        }
        if (state->flags & 4) {
            copy[stride - 2] = (row_tiles[stride - 2] & 0xFFF) | 0xD000;
            copy[stride - 1] = (row_tiles[stride - 1] & 0xFFF) | 0xD000;
        }
        row_tiles += state->stride;
        copy += state->field_1E;
    }
}
