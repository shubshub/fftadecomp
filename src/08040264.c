#include "ffta.h"

/* 0x08040264..0x08040280: 28 bytes. */
typedef struct {
    u8 unknown_00[0x1A];
    u16 value;
} CallbackState;

extern void func_0804018C(CallbackState *state);
extern void func_080401F4(CallbackState *state, u16 value);

void func_08040264(void *context, CallbackState *state)
{
    func_0804018C(state);
    func_080401F4(state, state->value * 2);
}
