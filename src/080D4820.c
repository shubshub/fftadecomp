#include "ffta.h"

/* 0x080D4820..0x080D4832: 18 bytes. */
typedef struct {
    u8 unknown_00[8];
    u16 value;
} HandleState;

extern HandleState *func_08005BFC(u32 handle);

void func_080D4820(u32 handle, u16 value)
{
    HandleState *state = func_08005BFC(handle);

    state->value = value;
}
