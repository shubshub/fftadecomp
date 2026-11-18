#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

struct ActionState {
    u8 unknown_00[8];
    Object *target;
    u8 unknown_0C[0x1A];
    u16 flags;
};

extern void func_08131DD4(u8 *state, s32 index);
extern u8 func_080CD8FC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern void func_080CDE5C(Object *object, u8 enabled);

/* Effect descriptor table 083A87B0, slot 35. */
void func_081324CC(struct ActionState *state)
{
    if (func_080CD8FC(state->target)) {
        if (!(state->flags & 0x10)) {
            func_080CDD88(state->target, 0);
            state->flags |= 0x100;
        }
    } else {
        func_08131DD4((u8 *)state, 10);
        if (!(state->flags & 0x10))
            func_080CDE5C(state->target, 1);
    }
}
