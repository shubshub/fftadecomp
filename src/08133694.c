#include "ffta.h"

struct State;

struct ActionState {
    u8 unknown00[8];
    struct State *target;
    u8 unknown0C[0x1A];
    u16 flags;
};

extern void func_081320E8(struct ActionState *state);
extern void func_080CE438(struct State *state, u8 value);

void func_08133694(struct ActionState *state)
{
    func_081320E8(state);
    if (!(state->flags & 0x110))
        func_080CE438(state->target, 1);
}
