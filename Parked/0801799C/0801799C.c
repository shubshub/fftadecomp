/* func_0801799C - 0x0801799C..0x08017A90, 244 bytes (pool at 0x08017A88).
 *
 * NOT YET MATCHING: same 115 instructions, but sb/sl hold i+1 / start*2 in
 * swapped order, `mov r5, sb` sits one slot early, and the 0x1FFFFF literal
 * load and the [sp, #8] reload before the func_0814186C call are in swapped order.
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

void func_0801799C(State0801799C *state, u32 index, u8 palette, u8 width)
{
    s8 row = index;
    u16 *row_tiles;
    u16 *copy;
    u8 stride;
    int start;
    int end;
    int i;
    int j;

    stride = state->stride;
    row_tiles = state->tiles
        + (u16)func_08142950((u16)((state->field_1A + row) << 1), state->rows << 1) * stride;
    copy = state->destination + (row << 1) * state->field_1E;

    if (palette == 0xFF)
        palette = state->palette;

    start = (state->flags & 2) ? 2 : 0;
    end = width;
    if (state->flags & 4)
        end -= 2;

    for (i = 0; i < 2; i++) {
        for (j = start; j < end; j++)
            row_tiles[j] = (row_tiles[j] & 0xFFF) | (palette << 12);
        func_0814186C(row_tiles + start, copy + start, (end - start) & 0x1FFFFF);
        row_tiles += state->stride;
        copy += state->field_1E;
    }
}
