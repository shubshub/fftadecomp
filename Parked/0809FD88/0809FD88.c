#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
} Point0809FD88;

/* Target bytes [0809FD88, 0809FDC0):
 * 30 B5 04 1C 0D 1C 00 20 21 5E 00 23 E8 5E 0B 1A
 * 00 2B 00 DA 5B 42 02 20 21 5E 02 24 28 5F 08 1A
 * 00 28 00 DA 40 42 83 42 00 DB 18 1C 11 1C A2 F0
 * 7F FC 30 BC 02 BC 08 47.
 */
s32 func_0809FD88(const Point0809FD88 *first,
                   const Point0809FD88 *second, s32 divisor)
{
    s32 delta_x = first->x - second->x;
    s32 delta_y;

    if (delta_x < 0)
        delta_x = -delta_x;
    delta_y = first->y - second->y;
    if (delta_y < 0)
        delta_y = -delta_y;
    if (delta_x >= delta_y)
        delta_y = delta_x;
    return delta_y / divisor;
}
