#include "ffta.h"

/* Complete target [0x080C127C, 0x080C13C6): 330 bytes. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} Unit;

typedef struct {
    Unit *unit;
} SearchEntry;

typedef struct {
    u8 unknown_00[0x3C];
    void *map;
} Context;

extern s32 func_08099F58(Context *context, s8 x, s8 y, u8 flags);
extern s32 func_081493AC(void *map, u8 x, u8 y);
extern s32 func_0809D6BC(s8 x, s8 y);

void func_080C127C(u32 unused, Context *context, SearchEntry *entry,
                   u8 *output_x, u8 *output_y, u8 *direction)
{
    s8 x = entry->unit->x;
    s8 y = entry->unit->y;
    s8 step_x;
    s8 step_y;
    s32 found;
    s32 best;
    s8 original_x = entry->unit->x;
    s8 original_y = entry->unit->y;

    do {
        found = 0;
        step_x = 1;
        step_y = -1;
        best = 255;
        --x;
        for (;;) {
            if (func_08099F58(context, x, y, 255)) {
                if ((u8)func_081493AC(context->map, (u8)x, (u8)y) < best) {
                    best = (u8)func_081493AC(context->map, (u8)x, (u8)y);
                    found = 1;
                    *output_x = x;
                    *output_y = y;
                }
            }
            x += step_x;
            y += step_y;
            if (original_x == x) {
                step_y = -step_y;
                if (step_x == 1 && step_y == -1)
                    break;
            }
            if (original_y == y) {
                step_x = -step_x;
                if (step_x == 1 && step_y == -1)
                    break;
            }
        }
    } while (!found);
    *direction = func_0809D6BC((s8)(entry->unit->x - *output_x),
                              (s8)(entry->unit->y - *output_y));
}
