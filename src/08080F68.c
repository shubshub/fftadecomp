#include "ffta.h"

/* Complete target [0x08080F68, 0x08081078), 272 bytes, 129 instructions
 * (literal pool 0x00000FFF, 0x001FFFFF at 0x08081070):
 * f0b557464e464546e0b486b080460c1c1206120e00921b061b0e0193407d8246
 * 051c240624164146488b00194004000cc97d4900c1f0d8fc0004000c68434000
 * 4246d1680f186400907f60434000916809180291009bff2b01d1d07f00904146
 * 0a8a0221081c10400004000c4042c01781464b460b409946042010402e1c0028
 * 00d0023e00204946490004915246520005924b46f31a039300244a4601308246
 * b24214da1848844600990d035000c319b21a201c01340199884204da19886046
 * 0840284318800233013a002af1d1049ab818029b99180d4a039b1a40c0f012fc
 * 05983f184146887f4000029a1218029250460128d0dd06b038bc9846a146aa46
 * f0bc01bc00470000ff0f0000ffff1f00
 *
 * Recolours up to `count` entries of two rows of a tile region and copies each
 * row out.  The copy is the 16-bit CpuSet in the CpuCopy16 shape: a size in
 * bytes halved into the halfword count, as src/0808AA18.c and src/0801799C.c
 * write it.
 */

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u16 *tiles;
    u16 flags;
    u8 unknown_12[3];
    u8 stride;
    u8 unknown_16;
    u8 rows;
    u8 unknown_18[2];
    u16 field_1A;
    u8 unknown_1C[2];
    u8 field_1E;
    u8 palette;
} State08080F68;

extern s32 func_08142950(s32 value, s32 divisor);
extern void func_0814186C(const void *source, void *destination, u32 count);

void func_08080F68(State08080F68 *state, s8 offset, u8 palette, u8 count)
{
    u16 *row_tiles;
    u16 *destination;
    u16 frame;
    s32 line;
    s32 start;
    s32 end;
    s32 size;
    /* One byte in two roles.  The ROM loads state->stride once (ldrb at
       0x08080F84) and keeps it in two registers: the row stride in sl
       (0x08080F86; doubled into [sp, #0x14] at 0x08080FF4 and added to
       row_tiles at 0x0808104A) and the row width in r5 (0x08080F88; the
       frame offset multiply at 0x08080FA4 and the span end at 0x08080FE4). */
    u32 stride = state->stride;
    u8 width = stride;
    s32 row;
    s32 column;
    s32 colored;

    frame = state->field_1A + offset;
    frame *= 2;
    frame = func_08142950(frame, state->rows * 2);
    row_tiles = state->tiles + frame * width;
    line = offset * 2;
    destination = state->destination + line * state->field_1E;
    if (palette == 0xFF)
        palette = state->palette;
    start = (state->flags & 2) ? 2 : 0;
    if (state->flags & 4)
        end = width - 2;
    else
        end = width;
    size = (end - start) * 2;
    for (row = 0; row < 2; row++) {
        colored = 0;
        for (column = start; column < end; column++) {
            if (colored++ < count)
                row_tiles[column] = (row_tiles[column] & 0xFFF) | (palette << 12);
        }
        func_0814186C(row_tiles + start, destination + start, (size / 2) & 0x1FFFFF);
        row_tiles += stride;
        destination += state->field_1E;
    }
}
