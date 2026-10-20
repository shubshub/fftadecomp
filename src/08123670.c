#include "ffta.h"

u16 func_0800A018(void);
void *func_08096D7C(void);
void func_08096E18(u16 index, void *context);

u32 func_08123670(void *context, const u8 *script)
{
    u16 index = func_0800A018();

    func_08096E18(index, func_08096D7C());
    return 0x110;
}
