#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u16 flags;
} EffectState;

extern void *func_08005BFC(void *task);

void func_080DFAEC(void *task)
{
    EffectState *state = func_08005BFC(task);

    state->flags &= ~0x8000;
    state->flags &= ~2;
}
