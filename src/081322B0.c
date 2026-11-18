#include "ffta.h"

struct ActionState {
    u8 unknown_00[8];
    void *target;
    u8 unknown_0C[0x1A];
    u16 flags;
};

struct UnitTimer {
    u8 unknown_00[0xD4];
    u16 timer;
};

struct State;
extern u8 func_080CD8FC(const void *object);
extern u8 func_080CDAAC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern void func_080CE02C(void *object, u8 enabled);
extern void func_080CE050(void *object, u8 enabled);
extern void func_080CE438(struct State *state, u8 value);
extern void func_08131DD4(u8 *buffer, s32 index);

/* Effect descriptor table 083A87B0, slot 28. */
void func_081322B0(struct ActionState *state)
{
    if (func_080CD8FC(state->target)) {
        if (!(state->flags & 0x10)) {
            func_080CDD88(state->target, 0);
            state->flags |= 0x100;
        }
    } else if (func_080CDAAC(state->target)) {
        func_08131DD4((u8 *)state, 23);
        if (!(state->flags & 0x10)) {
            func_080CE050(state->target, 1);
            func_080CE438(state->target, 2);
        }
    } else {
        func_08131DD4((u8 *)state, 22);
        if (!(state->flags & 0x10)) {
            struct UnitTimer *unit;
            func_080CE02C(state->target, 1);
            unit = state->target;
            unit->timer = 0;
        }
    }
}
