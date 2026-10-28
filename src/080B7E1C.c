#include "ffta.h"

extern void *func_08022840(u32 size);
extern void func_080B5278(void *state, void *context, u16 action,
                         u16 parameter, u8 argument4, u8 argument5,
                         u8 argument6);

/* Complete [0x080B7E1C, 0x080B7E7C): 96 bytes, 46 instructions. */
void *func_080B7E1C(void *context, u16 action, u16 parameter,
                    u8 argument3, u8 argument4, u8 argument5)
{
    void *state = func_08022840(0x1160);

    func_080B5278(state, context, action, parameter,
                   argument3, argument4, argument5);
    return state;
}
