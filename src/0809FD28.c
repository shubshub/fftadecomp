#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
} Point0809FD28;

/* The operation of func_0809FD88 (src/0809FD88.c), inlined.  Compiled out
 * of line this body also gives that function's 56 ROM bytes; it divides in
 * each arm, and src/0809FD88.c's text (select, then divide once) inlined
 * here gives 92 bytes, not the 94 at 0x0809FD28. */
static inline s32 distance_step(const Point0809FD28 *first,
                                const Point0809FD28 *second, s32 divisor)
{
    s32 delta_x = first->x - second->x;
    s32 delta_y;

    if (delta_x < 0)
        delta_x = -delta_x;
    delta_y = first->y - second->y;
    if (delta_y < 0)
        delta_y = -delta_y;
    if (delta_x >= delta_y)
        return delta_x / divisor;
    return delta_y / divisor;
}

/* Target bytes [0809FD28, 0809FD86):
 * F0 B5 47 46 80 B4 03 1C 0E 1C 15 1C 00 20 80 46
 * 00 27 70 1E 80 45 1C DA 1C 1C 00 22 A1 5E 04 23
 * E0 5E 0A 1A 00 2A 00 DA 52 42 02 20 21 5E 06 23
 * E0 5E 08 1A 00 28 00 DA 40 42 82 42 00 DB 10 1C
 * 29 1C A2 F0 A5 FC 80 44 04 34 01 37 70 1E 87 42
 * E3 DB 40 46 08 BC 98 46 F0 BC 02 BC 08 47.
 */
s32 func_0809FD28(const Point0809FD28 *points, s32 count, s32 divisor)
{
    s32 total = 0;
    s32 index;

    for (index = 0; index < count - 1; index++)
        total += distance_step(&points[index], &points[index + 1], divisor);
    return total;
}
