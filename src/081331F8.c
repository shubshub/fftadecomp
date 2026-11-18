#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    u8 unknown_00[8];
    Unit *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern u8 func_080CD8FC(const void *unit);
extern void func_080CDD88(void *unit, u8 enabled);
extern void func_08131DD4(void *state, s32 index);
extern void func_080CDE80(Unit *unit, u8 value);

void func_081331F8(ActionState *state)
{
    if (func_080CD8FC(state->target)) {
        func_080CDD88(state->target, 0);
        state->flags |= 0x100;
    } else {
        func_08131DD4(state, 11);
        if (!(state->flags & 0x10)) {
            func_080CDE80(state->target, 1);
        }
    }
}
