#include "ffta.h"

typedef struct {
    u8 unknown_00[0x34];
    u16 first;
    u16 second;
} ValueState;

extern ValueState *func_0800C614(void *object);
extern void func_0800CAF0(ValueState *state, u8 mode);
extern void func_0800C64C(void *object);

/* 0800DD30..0800DD5A: 42 bytes. */
void func_0800DD30(void *object, u16 first, u16 second)
{
    ValueState *state = func_0800C614(object);

    state->first = first;
    state->second = second;
    func_0800CAF0(state, 0);
    func_0800C64C(object);
}
