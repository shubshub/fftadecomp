#include "ffta.h"

typedef struct {
    u8 unknown_00[0xD4];
    u16 counter;
} Unit;

typedef struct {
    u8 unknown_00[8];
    Unit *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern u8 func_080CD8FC(const void *unit);
extern void func_080CDD88(void *unit, u8 enabled);
extern void func_08131DD4(void *state, s32 index);
extern void func_080CE02C(Unit *unit, u8 value);
extern u8 func_080CE3B8(const Unit *unit);
extern void func_080CE430(Unit *unit, u8 value);

void func_08132B44(ActionState *state)
{
    if (func_080CD8FC(state->target)) {
        if (!(state->flags & 0x10)) {
            func_080CDD88(state->target, 0);
            state->flags |= 0x100;
        }
    } else {
        u16 blocked;

        func_08131DD4(state, 22);
        blocked = state->flags & 0x10;
        if (!blocked) {
            s32 duration;

            func_080CE02C(state->target, 1);
            state->target->counter = 0;
            duration = func_080CE3B8(state->target);
            if (!(duration & 0x80)) {
                duration += 3;
                if (duration > 6)
                    duration = 6;
                func_080CE430(state->target, duration);
            }
        }
    }
}
