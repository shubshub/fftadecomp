#include "ffta.h"

/* 0x0813EC64..0x0813EC72: 14 bytes. */
typedef struct {
    u8 unknown_00[0x14];
    u16 values[4];
} ValueState;

extern void func_0814186C(const void *, void *, u32);

void func_0813EC64(const ValueState *state, u16 *values)
{
    func_0814186C(state->values, values, 4);
}
