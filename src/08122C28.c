#include "ffta.h"

extern void func_08126AA8(void *owner, const u8 *values, u8 mode);

u32 func_08122C28(void *state, const u8 *command)
{
    func_08126AA8(state, 0, 1);
    return 0x115;
}
