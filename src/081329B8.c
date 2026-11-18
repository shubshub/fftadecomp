#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    u8 unknown_00[8];
    Unit *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern void func_08131DD4(void *state, s32 index);
extern void func_080CE284(Unit *unit, u8 value);
extern void func_080CE2CC(Unit *unit, u8 value);

void func_081329B8(ActionState *state)
{
    func_08131DD4(state, 40);
    func_08131DD4(state, 42);
    if (!(state->flags & 0x10)) {
        func_080CE284(state->target, 1);
        func_080CE2CC(state->target, 1);
    }
}
