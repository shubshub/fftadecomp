#include "ffta.h"

/* 0x080BD7D4..0x080BD8CA: 246 bytes. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} Unit;

typedef struct {
    Unit *unit;
    u8 unknown_04[0x7C];
    void *search;
} Context;

u32 func_08099F58(Context *context, s8 x, s8 y, u8 flags);
u8 func_080BD35C(void *search, s8 x, s8 y, s8 mode);

void func_080BD7D4(Context *context, u8 *output_x, u8 *output_y, s8 mode)
{
    s32 radius;
    u8 original_x = context->unit->x;
    u8 original_y = context->unit->y;
    s32 x;
    s32 y;

    for (radius = 1; ; ++radius) {
        s32 step_x;
        s32 step_y;
        x = original_x - radius;
        y = original_y;
        step_x = 1;
        step_y = -1;

        do {
            if (func_08099F58(context, (s8)x, (s8)y, 0xFF)) {
                u8 result;

                context->unit->x = x;
                context->unit->y = y;
                result = func_080BD35C(context->search, (s8)x, (s8)y, mode);
                context->unit->x = original_x;
                context->unit->y = original_y;
                if (result == 0) {
                    *output_x = x;
                    *output_y = y;
                    return;
                }
            }

            if (original_x != x || original_y != y) {
                x += step_x;
                y += step_y;
                if (x == original_x) {
                    step_y = -step_y;
                    if (step_x == 1 && step_y == -1)
                        break;
                }
                if (y == original_y) {
                    step_x = -step_x;
                    if (step_x == 1 && step_y == -1)
                        break;
                }
            } else {
                break;
            }
        } while (1);
    }
}
