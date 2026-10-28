#include "ffta.h"

/* 0x0800DCF0..0x0800DD10: 32 bytes / 13 instructions. */
struct State0800DCF0 {
    u8 unknown_00[0x34];
    u16 value;
};

extern struct State0800DCF0 *func_0800C614(void *object);
extern void func_0800C9E4(struct State0800DCF0 *state, u32 mode);
extern void func_0800C64C(void *object);

void func_0800DCF0(void *object, u16 value)
{
    struct State0800DCF0 *state = func_0800C614(object);

    state->value = value;
    func_0800C9E4(state, 0);
    func_0800C64C(object);
}
