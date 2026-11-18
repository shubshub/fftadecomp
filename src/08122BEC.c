#include "ffta.h"

extern void func_08125884(void);

u32 func_08122BEC(void *state, const u8 *command)
{
    func_08125884();
    return 0x110;
}
