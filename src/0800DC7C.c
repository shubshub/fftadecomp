#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 first;
    u16 second;
} ValueState;

extern ValueState *func_0800C614(void *object);
extern void func_0800C64C(void *object);

/* 0800DC7C..0800DCA0: 36 bytes. */
void func_0800DC7C(void *object, u16 first, u16 second)
{
    ValueState *state = func_0800C614(object);

    state->first = first;
    state->second = second;
    func_0800C64C(object);
}
