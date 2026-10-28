#include "ffta.h"

/* 0x080B4678: 292 bytes. */
typedef struct {
    s8 x;
    s8 y;
    u8 map_value;
    u8 unknown_03;
} CandidateTile;

u32 func_080C92F0(void *object, u32 selector);
u32 func_080B7C94(u16 first, u16 second, u32 mode);
s32 func_080A0014(void *object, u8 origin_x, u8 origin_y,
                   u8 x, u8 y, u16 first, u16 second, u32 mode);
u8 func_0801CC18(u8 x, u8 y);

s32 func_080B4678(void *object, u8 origin_x, u8 origin_y,
                   u16 first, u16 second, CandidateTile *output)
{
    u32 raw_range;
    s32 range;
    s32 count;
    s32 radius;
    s32 x, y;
    s32 step_x, step_y;

    if (object != 0 && (func_080C92F0(object, 0x28) & 4))
        raw_range = 4;
    else
        raw_range = func_080B7C94(first, second, 0);
    range = (u8)raw_range;
    count = 0;

    for (radius = 0; radius <= range; radius++) {
        x = (s8)origin_x - radius;
        y = (s8)origin_y;
        step_x = 1;
        step_y = -1;
        do {
            if (func_080A0014(object, origin_x, origin_y, x, y,
                             first, second, 0)) {
                output->x = x;
                output->map_value = func_0801CC18(x, y);
                output->y = y;
                output++;
                count++;
            }
            if ((s8)origin_x == x && (s8)origin_y == y)
                break;
            x += step_x;
            y += step_y;
            if (x == (s8)origin_x) {
                step_y = -step_y;
                if (step_x == 1 && step_y == -1)
                    break;
            }
            if (y != (s8)origin_y)
                continue;
            step_x = -step_x;
            if (step_x == 1 && step_y == -1)
                break;
        } while (1);
    }
    return count;
}
