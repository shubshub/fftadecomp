#include "ffta.h"

struct Point080DA2D4 {
    s16 x;
    s16 y;
};

extern u32 func_08141874(u32 dividend, u32 divisor);

/* Complete [0x080DA2D4, 0x080DA3B8): 228 bytes, 112 instructions. */
u8 func_080DA2D4(const struct Point080DA2D4 *points, u16 count,
                 u16 *minimum_index)
{
    s16 maximum_y = points[0].y;
    s16 minimum_y = maximum_y;
    u16 minimum = 0;
    u16 maximum = 0;
    s32 index;
    u16 next;
    s16 first_x;
    s16 first_y;
    s16 second_x;
    s16 second_y;
    const struct Point080DA2D4 *third;
    s32 dx1;
    s32 dy1;
    s32 dx2;
    s32 dy2;

    for (index = 1; index < count; index++) {
        if (points[index].y < minimum_y) {
            minimum_y = points[index].y;
            minimum = index;
        }
        if (points[index].y > maximum_y) {
            maximum_y = points[index].y;
            maximum = index;
        }
    }

    *minimum_index = minimum;
    first_x = points[minimum].x;
    first_y = points[minimum].y;
    next = func_08141874((u16)(minimum + 1), count);
    second_x = points[next].x;
    second_y = points[next].y;
    if (maximum == next)
        maximum++;
    third = &points[(u16)func_08141874(maximum, count)];
    dx1 = second_x - first_x;
    dy1 = second_y - first_y;
    dx2 = third->x - first_x;
    dy2 = third->y - first_y;
    if (dy2 * dx1 - dy1 * dx2 >= 0)
        return 1;
    return 0;
}
