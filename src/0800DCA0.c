#include "ffta.h"

/* 0x0800DCA0..0x0800DCC4: 36 bytes / 16 instructions. */
struct State0800DCA0 {
    u8 unknown_00[6];
    u16 first;
    u16 second;
};

extern struct State0800DCA0 *func_0800C614(void *object);
extern void func_0800C64C(void *object);

void func_0800DCA0(void *object, u16 first, u16 second)
{
    struct State0800DCA0 *state = func_0800C614(object);

    state->first = first;
    state->second = second;
    func_0800C64C(object);
}
