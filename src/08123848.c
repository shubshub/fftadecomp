#include "ffta.h"

void *func_08096D7C(void);
void func_0809A260(void *context, u32 value);
void func_080A9548(void);

u32 func_08123848(void *context, const u8 *script)
{
    func_0809A260(func_08096D7C(), 0);
    func_080A9548();
    return 0x110;
}
