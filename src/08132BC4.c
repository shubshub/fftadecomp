#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    u8 unknown_00[8];
    Unit *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern void func_08131DD4(void *state, s32 index);
extern void func_080CE008(Unit *unit, u8 value);
extern u8 func_080CE3B0(const Unit *unit);
extern void func_080CE428(Unit *unit, u8 value);

void func_08132BC4(ActionState *state)
{
    func_08131DD4(state, 21);
    if (!(state->flags & 0x10)) {
        s32 duration;

        func_080CE008(state->target, 1);
        duration = func_080CE3B0(state->target) + 3;
        if (!(duration & 0x80)) {
            if (duration >= 6)
                duration = 6;
            func_080CE428(state->target, duration);
        }
    }
}
