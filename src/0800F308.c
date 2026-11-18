#include "polygon_scanline.h"

/* Target: complete [0x0800F308, 0x0800F480), 376 executable bytes. */
extern s32 func_08141874(s32, s32);

void func_0800F308(const PolygonPoint *vertices, u16 count,
                  s16 x_offset, s16 y_offset, PolygonSpan *ranges,
                  u8 mode)
{
    u16 first;
    u8 direction = func_0800DECC(vertices, count, &first);
    s16 first_x = vertices[first].x;
    s16 first_y = vertices[first].y;
    s16 y_base = 0;
    s16 previous_x, previous_y;
    u16 i;

    if (mode == 0) {
        y_base = first_y;
        first_y = 0;
    }
    previous_x = first_x;
    previous_y = first_y;
    for (i = 1; i < count; i++) {
        u16 index = func_08141874((u16)(first + i), count);
        s16 x = x_offset + vertices[index].x;
        s16 y = y_offset + vertices[index].y - y_base;

        if (direction) {
            if (previous_y < y)
                func_0800E05C(previous_x, previous_y, x, y, ranges);
            else
                func_0800DFB0(previous_x, previous_y, x, y, ranges);
        } else {
            if (previous_y < y)
                func_0800DFB0(previous_x, previous_y, x, y, ranges);
            else
                func_0800E05C(previous_x, previous_y, x, y, ranges);
        }
        previous_x = x;
        previous_y = y;
    }
    if (direction) {
        if (previous_y < first_y)
            func_0800E05C(previous_x, previous_y, first_x, first_y, ranges);
        else
            func_0800DFB0(previous_x, previous_y, first_x, first_y, ranges);
    } else {
        if (previous_y < first_y)
            func_0800DFB0(previous_x, previous_y, first_x, first_y, ranges);
        else
            func_0800E05C(previous_x, previous_y, first_x, first_y, ranges);
    }
}
