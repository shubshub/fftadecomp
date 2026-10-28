#include "ffta.h"

typedef struct {
    u16 x;
    u16 y;
} Point0800DECC;

extern s32 func_08141874(s32 numerator, s32 denominator);

/* 0x0800DECC - 228 bytes. */
u32 func_0800DECC(const Point0800DECC *points, u16 count, u16 *minimum_index)
{
    u16 maximum_y = points[0].y;
    u16 minimum_y = maximum_y;
    u16 minimum = 0;
    u16 maximum = 0;
    s32 i;
    u16 next;
    u16 opposite;
    u16 third;
    const Point0800DECC *c;
    u16 ax;
    u16 ay;
    u16 bx;
    u16 by;
    s32 abx;
    s32 aby;
    s32 acx;
    s32 acy;

    for (i = 1; i < count; i++) {
        if ((s16)points[i].y < (s16)minimum_y) {
            minimum_y = points[i].y;
            minimum = i;
        }
        if ((s16)points[i].y > (s16)maximum_y) {
            maximum_y = points[i].y;
            maximum = i;
        }
    }
    *minimum_index = minimum;
    ax = points[minimum].x;
    ay = points[minimum].y;
    next = func_08141874((u16)(minimum + 1), count);
    bx = points[next].x;
    by = points[next].y;
    opposite = maximum;
    if (opposite == next)
        opposite++;
    third = func_08141874(opposite, count);
    c = &points[third];
    abx = (s16)bx - (s16)ax;
    aby = (s16)by - (s16)ay;
    acx = (s16)c->x - (s16)ax;
    acy = (s16)c->y - (s16)ay;
    if (abx * acy - aby * acx >= 0)
        return 1;
    return 0;
}
