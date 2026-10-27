#include "ffta.h"

typedef struct {
    u8 unknown_00[0x34];
    u16 value;
} ValueState;

extern ValueState *func_0800C614(void *object);
extern void func_0800C9E4(ValueState *state, u32 mode);
extern void func_0800C64C(void *object);

/* 0800DD10..0800DD30: 32 bytes, 13 instructions. */
void func_0800DD10(void *object, u16 value)
{
    ValueState *state = func_0800C614(object);

    state->value = value;
    func_0800C9E4(state, 1);
    func_0800C64C(object);
}
