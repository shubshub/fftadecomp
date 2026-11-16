/* Complete target [0x0801799C, 0x08017A90), 244 bytes, 115 instructions
 * (literal pool 0x00000FFF, 0x001FFFFF at 0x08017A88):
 * f0b557464e464546e0b483b0061c0c1c1206120e00921b061b0e9946757d2406
 * 2416708b00194004000cf17d49002af1c1ff0004000c68434000f1680f186400
 * b07f60434000b168091801910098ff2801d1f17f0091328a0221081c10400004
 * 000c4042c017804643460b409846042010404d46002800d0023d002041464900
 * 8a464346eb1a0293424601308146aa420fda1648844600990c035000c319aa1a
 * 198860460840204318800233013a002af6d15346f818019951440d4a029b1a40
 * 29f106ff707d40003f18b07f400001990918019148460128d6dd03b038bc9846
 * a146aa46f0bc01bc00470000ff0f0000ffff1f00
 *
 * Recolours two rows of a tile region and copies them out.  The source row is
 * (field_1A + row) * 2 wrapped by rows * 2 through func_08142950 (signed
 * remainder); the destination row is row * 2.  A 0xFF palette selects the
 * region's own; `flags & 2` and `flags & 4` trim two columns from the left and
 * the right.  Each entry from start to end gets `palette << 12` as its top
 * nibble, then the span is copied with the 16-bit CpuSet (func_0814186C).
 */

#include "ffta.h"

typedef struct {
    u8   unknown_00[0x08];
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
    u8   palette;
} State0801799C;

s32 func_08142950(s32 numerator, s32 denominator);
void func_0814186C(const void *source, void *destination, u32 control);

void func_0801799C(State0801799C *state, s8 row, u8 palette, u8 width)
{
    u16 *row_tiles;
    u16 *copy;
    u8 stride;
    int start;
    int end;
    int size;
    int i;
    int j;

    stride = state->stride;
    row_tiles = state->tiles
        + (u16)func_08142950((u16)((state->field_1A + row) << 1), state->rows << 1) * stride;
    copy = state->destination + (row << 1) * state->field_1E;

    if (palette == 0xFF)
        palette = state->palette;

    start = (state->flags & 2) ? 2 : 0;
    if (state->flags & 4)
        end = width - 2;
    else
        end = width;

    /* The copy size in bytes, halved into the CpuSet halfword count as
     * src/0808AA18.c halves the same signed byte size.  Here the halving
     * folds: the ROM keeps end - start (0x08017A20, [sp, #8]) and masks it at
     * 0x08017A56.  The same-record sibling at 0x08017734 keeps the byte size
     * itself: (width - 2) << 1 before its loop (0x0801776E), asrs #1 at the
     * call (0x080177C4). */
    size = (end - start) * 2;
    for (i = 0; i < 2; i++) {
        for (j = start; j < end; j++)
            row_tiles[j] = (row_tiles[j] & 0xFFF) | (palette << 12);
        func_0814186C(row_tiles + start, copy + start, (size / 2) & 0x1FFFFF);
        row_tiles += state->stride;
        copy += state->field_1E;
    }
}
