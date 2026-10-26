#include "ffta.h"

extern void func_08126B6C(void *, u32, u32, u32);

/* Complete [0x08122D04, 0x08122D20): 28 bytes, 10 instructions. */
u32 func_08122D04(void *state, const u8 *command)
{
    func_08126B6C(state, command[1], command[2], command[3]);
    return 0x115;
}
