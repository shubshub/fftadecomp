#include "ffta.h"

// Complete [0x080DA77C, 0x080DA8A0): 292 bytes, 146 instructions.
// Draw the closed outline of a polygon, starting at the vertex picked by
// func_080DA2D4 and choosing the edge drawer by edge direction and winding.

struct Point080DA77C {
    s16 x;
    s16 y;
};

extern u8 func_080DA2D4(const struct Point080DA77C *points, u16 count,
                        u16 *minimum_index);
extern u32 func_08141874(u32 dividend, u32 divisor);
extern void func_080DA3B8(s16 first_x, s16 first_y, s16 second_x,
                          s16 second_y, void *context);
extern void func_080DA598(s16 first_x, s16 first_y, s16 second_x,
                          s16 second_y, void *context);

void func_080DA77C(const struct Point080DA77C *points, u16 count,
                   void *context)
{
    u16 start;
    s16 first_x;
    s16 first_y;
    s16 previous_x;
    s16 previous_y;
    u16 index;
    u8 winding;

    winding = func_080DA2D4(points, count, &start);
    first_x = points[start].x;
    first_y = points[start].y;
    previous_x = first_x;
    previous_y = first_y;

    for (index = 1; index < count; index++) {
        u16 vertex = func_08141874((u16)(start + index), count);
        s16 x = points[vertex].x;
        s16 y = points[vertex].y;

        if (winding) {
            if (previous_y < y)
                func_080DA598(previous_x, previous_y, x, y, context);
            else
                func_080DA3B8(previous_x, previous_y, x, y, context);
        } else {
            if (previous_y < y)
                func_080DA3B8(previous_x, previous_y, x, y, context);
            else
                func_080DA598(previous_x, previous_y, x, y, context);
        }
        previous_x = x;
        previous_y = y;
    }

    if (winding) {
        if (previous_y < first_y)
            func_080DA598(previous_x, previous_y, first_x, first_y, context);
        else
            func_080DA3B8(previous_x, previous_y, first_x, first_y, context);
    } else {
        if (previous_y < first_y)
            func_080DA3B8(previous_x, previous_y, first_x, first_y, context);
        else
            func_080DA598(previous_x, previous_y, first_x, first_y, context);
    }
}
