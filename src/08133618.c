#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

typedef struct ActionState {
    u8 unknown_00[8];
    Object *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern void func_08131DD4(u8 *buffer, s32 index);
extern void func_080CDEC8(Object *object, u8 enabled);

void func_08133618(ActionState *state)
{
    func_08131DD4((u8 *)state, 0x0D);
    if (!(state->flags & 0x10))
        func_080CDEC8(state->target, 1);
}
