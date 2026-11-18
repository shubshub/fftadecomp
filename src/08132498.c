#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE8];
    u8 flags;
} Object;

struct ActionState {
    u8 unknown_00[8];
    Object *target;
    u8 unknown_0C[0x1A];
    u16 flags;
};

extern void func_08131DD4(u8 *state, s32 index);
extern void func_080CDD40(Object *unit, u8 enabled);

/* Effect descriptor table 083A87B0, slot 33. */
void func_08132498(struct ActionState *state)
{
    func_08131DD4((u8 *)state, 2);
    if (!(state->flags & 0x10))
        func_080CDD40(state->target, 1);
}
