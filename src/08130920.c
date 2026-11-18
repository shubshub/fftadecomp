#include "ffta.h"

typedef struct ActionState {
    void *source;
    void *target;
    void *selected_target;
} ActionState;

extern u8 func_080C8280(const void *unit);

u8 func_08130920(ActionState *state)
{
    if (func_080C8280(state->target))
        return 0;
    return state->selected_target != 0;
}
