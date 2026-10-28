#include "ffta.h"

/* 0x080DF8CC..0x080DF8E8: 28 bytes. */
extern void func_080DE150(void *state, u32 selector, u32 value);

void func_080DF8CC(void *state)
{
    func_080DE150(state, 10, 0);
    func_080DE150(state, 9, 0);
}
