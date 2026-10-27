#include "ffta.h"

/* 0x0813EC04..0x0813EC26: 34 bytes, 16 instructions. */
typedef struct {
    u8 mode;
    u8 unknown_01[0x0B];
    u8 destination[0x10];
    u32 field_1C;
    u32 field_20;
} State;

extern void func_0814186C(const void *source, void *destination, u32 count);

void func_0813EC04(State *state, const void *source, u32 value)
{
    func_0814186C(source, state->destination, 4);
    state->field_1C = 0;
    state->field_20 = value;
    state->mode = 2;
}
