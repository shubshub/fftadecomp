#include "ffta.h"

struct Unit {
    u8 unknown_00[9];
    u8 level;
};

struct ActionState {
    u8 unknown_00[4];
    struct Unit *unit;
};

struct GameState {
    u8 unknown_0000[0x2FBB];
    u8 field_2FBB;
};

extern struct GameState g_state_02000000;
extern u8 func_080C8280(const void *unit);

/* Action condition table 083A8604, slot 14. */
u8 func_08130BF4(struct ActionState *state)
{
    u8 state_digit;
    u8 level_digit;

    if (func_080C8280(state->unit))
        return 0;
    state_digit = g_state_02000000.field_2FBB % 10u;
    level_digit = state->unit->level % 10u;
    return state_digit == level_digit;
}
