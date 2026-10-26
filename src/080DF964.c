#include "ffta.h"

/* 0x080DF964..0x080DF976: 18 bytes. */
typedef struct {
    u8 unknown_00[0x14];
    u16 value;
} HalfwordValueState;

extern HalfwordValueState *func_08005BFC(u32 handle);

void func_080DF964(u32 handle, u16 value)
{
    HalfwordValueState *state = func_08005BFC(handle);

    state->value = value;
}
