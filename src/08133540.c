#include "ffta.h"

struct Object;

typedef struct ActionState {
    u8 unknown_00[8];
    struct Object *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern u8 func_080CD8FC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern void func_08131DD4(u8 *buffer, s32 index);
extern void func_080CE124(void *object, u8 enabled);
extern void func_080CE468(struct Object *object, u8 value);

void func_08133540(ActionState *state)
{
    if (func_080CD8FC(state->target)) {
        if (!(state->flags & 0x10)) {
            func_080CDD88(state->target, 0);
            state->flags |= 0x100;
        }
    } else {
        func_08131DD4((u8 *)state, 0x1D);
        if (!(state->flags & 0x10)) {
            func_080CE124(state->target, 1);
            func_080CE468(state->target, 3);
        }
    }
}
