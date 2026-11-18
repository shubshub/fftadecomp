#include "ffta.h"

typedef struct Unit {
    u8 unknown_00[0x2A];
    u16 equipment[5];
} Unit;

typedef struct ActionState {
    Unit *source;
    Unit *target;
} ActionState;

extern u8 func_080C8280(const void *unit);
extern s32 func_080CA7A4(u16 item, u8 selector);

/* An equipped item in any of categories 1 through 9 satisfies this condition. */
u8 func_08130944(ActionState *state)
{
    Unit *unit;
    s32 i;

    if (func_080C8280(state->target))
        return 0;
    unit = state->target;
    for (i = 0; i < 5; i++) {
        u16 item = unit->equipment[i];

        if (item != 0) {
            u8 category = func_080CA7A4(item, 3);

            if ((u8)(category - 1) < 9)
                return 1;
        }
    }
    return 0;
}
