#include "ffta.h"

typedef struct {
    u8 active;
    u8 kind;
    u8 unknown_02[2];
    u8 first[0x10];
    u8 second[8];
    u32 field_1C;
    u32 field_20;
} State;

extern void func_0814186C(const void *source, void *destination, u32 count);

/* Complete [0x0813EC28, 0x0813EC5A): 50 bytes, 23 instructions. */
void func_0813EC28(State *state, const void *source, u32 value)
{
    if (source != 0) {
        func_0814186C(source, state->first, 4);
        func_0814186C(source, state->second, 4);
    }
    state->field_1C = 0;
    state->field_20 = value;
    state->active = 1;
}
