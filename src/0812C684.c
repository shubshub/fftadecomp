#include "ffta.h"

/* 0x0812C684..0x0812C6FE: 122 bytes. */
u8 func_0812C684(s8 x, s8 y, s8 origin_x, s8 origin_y,
                s8 direction_x, s8 direction_y)
{
    s8 delta_x = x - origin_x;
    s8 delta_y = y - origin_y;
    s8 distance_x = delta_x < 0 ? -delta_x : delta_x;
    s8 distance_y = delta_y < 0 ? -delta_y : delta_y;

    if (delta_x * direction_x < 0 || delta_y * direction_y < 0)
        return 0;
    if (direction_x != 0) {
        if (distance_y > distance_x)
            return 0;
    } else {
        if (distance_x > distance_y)
            return 0;
    }
    return 1;
}
