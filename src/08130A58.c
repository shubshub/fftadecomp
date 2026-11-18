#include "ffta.h"

typedef struct ActionState {
    void *source;
    void *target;
} ActionState;

extern u8 func_080C8240(void *unit);
extern u8 func_080C8280(const void *unit);

u8 func_08130A58(ActionState *state)
{
    u8 source_flag;
    u8 target_flag;

    if (func_080C8280(state->target))
        return 0;
    source_flag = func_080C8240(state->source);
    target_flag = func_080C8240(state->target);
    return source_flag == target_flag;
}
