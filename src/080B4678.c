#include "ffta.h"

struct Tile {
    u8 x;
    u8 y;
    u8 value;
    u8 unknown_03;
};

extern u32 func_080C92F0(void *unit, u32 selector);
extern u8 func_080B7C94(u16 ability, u16 parameter, s32 mode);
extern u8 func_0801CC18(u8 x, u8 y);
extern s32 func_080A0014(void *owner, u8 start_x, u8 start_y,
    u8 x, u8 y, u16 first, u16 second, u8 flags);

/* An inlined copy of func_080B7DC8 (src/080B7DC8.c). */
static inline u8 inlined_080B7DC8(void *unit, u16 ability, u16 parameter, s32 mode)
{
    if (unit != 0 && (func_080C92F0(unit, 0x28) & 4)) {
        if (mode == 0)
            return 4;
        return 1;
    }
    return func_080B7C94(ability, parameter, mode);
}

/* Complete [0x080B4678, 0x080B479C): 292 bytes, 142 instructions. */
s32 func_080B4678(void *owner, s8 x, s8 y, u16 first, u16 second,
    struct Tile *tiles)
{
    s32 range;
    s32 count;
    s32 distance;
    s32 current_x;
    s32 current_y;
    s32 step_x;
    s32 step_y;

    range = inlined_080B7DC8(owner, first, second, 0);
    count = 0;
    for (distance = 0; distance <= range; distance++) {
        current_x = x - distance;
        current_y = y;
        step_x = 1;
        step_y = -1;

        while (1) {
            if (func_080A0014(owner, x, y, current_x, current_y, first, second, 0)) {
                tiles->x = current_x;
                tiles->value = func_0801CC18(current_x, current_y);
                tiles->y = current_y;
                tiles++;
                count++;
            }

            if (x == current_x && y == current_y)
                break;

            current_x += step_x;
            current_y += step_y;
            if (current_x == x) {
                step_y = -step_y;
                if (step_x == 1 && step_y == -1)
                    break;
            }
            if (current_y == y) {
                step_x = -step_x;
                if (step_x == 1 && step_y == -1)
                    break;
            }
        }
    }

    return count;
}
