#include "ffta.h"

struct ActionState {
    u8 unknown_00[8];
    void *target;
    u8 unknown_0C[0x1A];
    u16 flags;
};

extern void func_08131DD4(u8 *state, s32 index);
extern u8 func_080CD8FC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern void func_080CDFE4(void *object, u8 enabled);
extern void func_080CE420(void *object, u8 value);

/* Effect descriptor table 083A87B0, slot 42. */
void func_08132654(struct ActionState *state)
{
    if (func_080CD8FC(state->target)) {
        if (!(state->flags & 0x10)) {
            func_080CDD88(state->target, 0);
            state->flags |= 0x100;
        }
    } else {
        func_08131DD4((u8 *)state, 20);
        if (!(state->flags & 0x10)) {
            func_080CDFE4(state->target, 1);
            func_080CE420(state->target, 3);
        }
    }
}
