#include "ffta.h"

struct Unit {
    u8 unknown_00[9];
    u8 level;
};

struct ActionState {
    struct Unit *source;
    struct Unit *target;
};

extern u8 func_080C8280(const void *unit);
extern u8 func_081308F4(const struct Unit *unit);

/* Action condition table 083A8604, slot 9. */
u8 func_08130AAC(struct ActionState *state)
{
    u8 source_digit;
    u8 target_digit;

    if (func_080C8280(state->target) || func_081308F4(state->target))
        return 0;
    source_digit = state->source->level % 10u;
    target_digit = state->target->level % 10u;
    return source_digit == target_digit;
}
