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
extern u8 func_080CD8FC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern void func_080CDDF4(Object *object, u8 enabled);

/* Effect descriptor table 083A87B0, slot 27. */
void func_08132268(struct ActionState *state)
{
    if (func_080CD8FC(state->target)) {
        func_080CDD88(state->target, 0);
        state->flags |= 0x100;
    } else {
        func_08131DD4((u8 *)state, 7);
        if (!(state->flags & 0x10))
            func_080CDDF4(state->target, 1);
    }
}
