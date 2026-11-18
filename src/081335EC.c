#include "ffta.h"

struct Object;

typedef struct ActionState {
    u8 unknown_00[8];
    struct Object *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern void func_08131DD4(u8 *buffer, s32 index);
extern void func_080CE070(void *object, u8 enabled);
extern void func_080CE440(struct Object *object, u8 value);

void func_081335EC(ActionState *state)
{
    func_08131DD4((u8 *)state, 0x18);
    if (!(state->flags & 0x10)) {
        func_080CE070(state->target, 1);
        func_080CE440(state->target, 3);
    }
}
