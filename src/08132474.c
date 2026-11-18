#include "ffta.h"

struct ActionState {
    u8 unknown_00[8];
    void *target;
    u8 unknown_0C[0x1A];
    u16 flags;
};

extern void func_08131DD4(u8 *state, s32 index);
extern void func_080CDDAC(void *unit, u8 enabled);

/* Effect descriptor table 083A87B0, slot 32. */
void func_08132474(struct ActionState *state)
{
    func_08131DD4((u8 *)state, 5);
    if (!(state->flags & 0x10))
        func_080CDDAC(state->target, 1);
}
