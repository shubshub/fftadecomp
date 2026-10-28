#include "ffta.h"

/* Target: complete [0x08124ACC, 0x08124BB4), 232 bytes, 107 instructions. */
typedef struct {
    u8 x;
    u8 map_value;
    u8 y;
} Point08124ACC;

extern u8 func_0801CC18(u8 column, u8 row);

u8 func_08124ACC(u8 start_x, u8 start_y, u8 end_x, u8 end_y)
{
    Point08124ACC start, end;

    start.x = start_x;
    start.y = start_y;
    end.x = end_x;
    end.y = end_y;
    start.map_value = func_0801CC18(start.x, start.y);
    end.map_value = func_0801CC18(end.x, end.y);

    if (start.x == end.x) {
        if (start.y < end.y)
            return 0;
        else
            return 2;
    } else if (start.y == end.y) {
        if (start.x < end.x)
            return 3;
        else
            return 1;
    } else if (start.x > end.x) {
        if (start.y > end.y) {
            if (start.y - end.y > start.x - end.x)
                return 2;
            else
                return 1;
        } else {
            if (end.y - start.y > start.x - end.x)
                return 0;
            else
                return 1;
        }
    } else {
        if (start.y > end.y) {
            if (start.y - end.y > end.x - start.x)
                return 2;
            else
                return 3;
        } else {
            if (end.y - start.y > end.x - start.x)
                return 0;
            else
                return 3;
        }
    }
}
