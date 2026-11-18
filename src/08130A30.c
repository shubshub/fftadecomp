#include "ffta.h"

typedef struct ActionState {
    void *source;
    void *target;
} ActionState;

extern u8 func_080C8280(const void *unit);

u8 func_08130A30(ActionState *state)
{
    if (func_080C8280(state->target))
        return 0;
    return state->source == state->target;
}
