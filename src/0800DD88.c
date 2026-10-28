#include "ffta.h"

typedef struct {
    u8 unknown_00[0x34];
    u16 first;
    u16 second;
} ValueState;

extern ValueState *func_0800C614(void *object);
extern void func_0800CBFC(ValueState *state);
extern void func_0800C64C(void *object);

/* 0800DD88..0800DDB0: 40 bytes. */
void func_0800DD88(void *object, u16 first, u16 second)
{
    ValueState *state = func_0800C614(object);

    state->first = first;
    state->second = second;
    func_0800CBFC(state);
    func_0800C64C(object);
}
