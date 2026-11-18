#include "ffta.h"

typedef struct Unit Unit;

typedef struct ActionState {
    Unit *source;
    Unit *target;
} ActionState;

extern u8 func_080C8280(const void *unit);
extern u8 func_081308F4(const Unit *unit);

u8 func_08130A0C(ActionState *state)
{
    if (func_081308F4(state->target))
        return 0;
    return func_080C8280(state->target);
}
