#include "ffta.h"

/* 0x080D8B18..0x080D8B28: 16 bytes. */
typedef struct {
    u8 unknown_00[0x20];
    u32 value;
} HandleValueState;

extern HandleValueState *func_08005BFC(u32 handle);

void func_080D8B18(u32 handle, u32 value)
{
    HandleValueState *state = func_08005BFC(handle);

    state->value = value;
}
