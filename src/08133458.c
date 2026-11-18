#include "ffta.h"

typedef struct ActionState {
    u8 unknown_00[8];
    void *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern void func_08131DD4(u8 *buffer, s32 index);
extern void func_080CE264(void *object, u8 enabled);

void func_08133458(ActionState *state)
{
    func_08131DD4((u8 *)state, 0x27);
    if (!(state->flags & 0x10))
        func_080CE264(state->target, 1);
}
