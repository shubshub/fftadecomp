#include "ffta.h"

/* 0x080D3940..0x080D3958: 24 bytes. */
typedef struct {
    u32 unknown_00;
    u32 value;
} HandleState;

extern u32 data_020159C0;
extern HandleState *func_08005BFC(u32 handle);

void func_080D3940(u32 value)
{
    HandleState *state = func_08005BFC(data_020159C0);

    state->value = value;
}
