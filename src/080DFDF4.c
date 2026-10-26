#include "ffta.h"

extern u16 func_08005BAC(void *task);
extern void func_08005BA8(void *task, u16 state);

/* Complete [0x080DFDF4, 0x080DFE28): 52 bytes, 21 instructions. */
u8 func_080DFDF4(void *task)
{
    u8 ready = func_08005BAC(task) == 0x101;

    if (!ready)
        return 0;
    func_08005BA8(task, 0x100);
    return 1;
}
