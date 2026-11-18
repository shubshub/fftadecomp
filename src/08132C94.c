#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    u8 unknown_00[8];
    Unit *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern void func_08131DD4(void *state, s32 index);
extern void func_080CDF10(Unit *unit, u8 value);

void func_08132C94(ActionState *state)
{
    func_08131DD4(state, 15);
    if (!(state->flags & 0x10)) {
        func_080CDF10(state->target, 1);
    }
}
