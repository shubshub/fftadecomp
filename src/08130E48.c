#include "ffta.h"

struct Unit;
struct ActionState {
    struct Unit *entry;
    struct Unit *unit;
    u8 unknown_08[4];
    u16 action;
};

extern u8 func_08130DCC(struct ActionState *state);
extern u8 func_080CD95C(const struct Unit *unit);
extern s32 func_080C7EA4(const void *unit, u32 field);

/* Action condition table 083A8604, slot 26. Field 3 reads the unit's job. */
u8 func_08130E48(struct ActionState *state)
{
    if (!func_08130DCC(state) || func_080CD95C(state->unit))
        return 0;

    switch (state->action) {
    case 0xBD:
        if (func_080C7EA4(state->unit, 3) == 6)
            return 1;
        break;
    case 0xBE:
        if (func_080C7EA4(state->unit, 3) == 7)
            return 1;
        break;
    case 0xBF:
        if (func_080C7EA4(state->unit, 3) == 8)
            return 1;
        break;
    case 0xC0:
        if (func_080C7EA4(state->unit, 3) == 9)
            return 1;
        break;
    case 0xC1:
        if (func_080C7EA4(state->unit, 3) == 10)
            return 1;
        break;
    case 0xC2:
        if (func_080C7EA4(state->unit, 3) == 11)
            return 1;
        break;
    case 0xC3:
        if (func_080C7EA4(state->unit, 3) == 13)
            return 1;
        break;
    case 0xC4:
        if (func_080C7EA4(state->unit, 3) == 14)
            return 1;
        break;
    case 0xC5:
        if (func_080C7EA4(state->unit, 3) == 15)
            return 1;
        break;
    case 0xC6:
        if (func_080C7EA4(state->unit, 3) == 16)
            return 1;
        break;
    case 0xC7:
        if (func_080C7EA4(state->unit, 3) == 17)
            return 1;
        break;
    case 0xC8:
        if (func_080C7EA4(state->unit, 3) == 18)
            return 1;
        break;
    case 0xC9:
        if (func_080C7EA4(state->unit, 3) == 12)
            return 1;
        break;
    }
    return 0;
}
