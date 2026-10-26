#include "ffta.h"

extern void *func_08022840(u32 size);
extern void func_080A7D60(void *state, void *context);

/* Complete [0x080A8A90, 0x080A8AAA): 26 bytes, 11 instructions. */
void *func_080A8A90(void *context)
{
    void *state = func_08022840(0x50);

    func_080A7D60(state, context);
    return state;
}
