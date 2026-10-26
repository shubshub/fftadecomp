#include "ffta.h"

extern void *func_08022840(u32 size);
extern void func_080BBBB0(void *state, void *context, u16 parameter);

/* Complete [0x080BC914, 0x080BC934): 32 bytes, 14 instructions. */
void *func_080BC914(void *context, u16 parameter)
{
    void *state = func_08022840(0x54);

    func_080BBBB0(state, context, parameter);
    return state;
}
