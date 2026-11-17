#include "ffta.h"

// Target: complete [0x0800F480, 0x0800F6A6), 550 executable bytes.
typedef struct {
    s16 x;
    s16 y;
} Point0800F480;

typedef struct {
    u16 start;
    u16 end;
} Range0800F480;

typedef struct {
    s16 center_x;
    s16 center_y;
    s16 scale_x;
    s16 scale_y;
} Scale0800F480;

extern s32 func_0800DECC(const Point0800F480 *, u16, u16 *);
extern void func_0800DFB0(s16, s16, s16, s16, Range0800F480 *);
extern void func_0800E05C(s16, s16, s16, s16, Range0800F480 *);
extern s32 func_08141874(s32, s32);

static inline void scale_point(s16 *x, s16 *y, const Scale0800F480 *s)
{
    s32 delta;

    delta = *x - s->center_x;
    delta *= s->scale_x;
    *x = (delta >> 8) + s->center_x;
    delta = *y - s->center_y;
    delta *= s->scale_y;
    *y = (delta >> 8) + s->center_y;
}

void func_0800F480(const Point0800F480 *vertices, u16 count,
                  s16 x_offset, s16 y_offset, Range0800F480 *ranges,
                  u8 mode, const Scale0800F480 *scale)
{
    u16 first;
    s16 start_x, start_y;
    s16 x, y;
    u8 direction = func_0800DECC(vertices, count, &first);
    s16 y_base;
    s16 previous_x, previous_y;
    u16 i;

    start_x = vertices[first].x;
    start_y = vertices[first].y;
    scale_point(&start_x, &start_y, scale);
    y_base = 0;
    if (mode == 0) {
        y_base = start_y;
        start_y = 0;
    }
    previous_x = start_x;
    previous_y = start_y;
    for (i = 1; i < count; i++) {
        u16 index = func_08141874((u16)(first + i), count);

        x = x_offset + vertices[index].x;
        y = y_offset + vertices[index].y - y_base;
        scale_point(&x, &y, scale);

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
        if (previous_y < start_y)
            func_0800E05C(previous_x, previous_y, start_x, start_y, ranges);
        else
            func_0800DFB0(previous_x, previous_y, start_x, start_y, ranges);
    } else {
        if (previous_y < start_y)
            func_0800DFB0(previous_x, previous_y, start_x, start_y, ranges);
        else
            func_0800E05C(previous_x, previous_y, start_x, start_y, ranges);
    }
}
