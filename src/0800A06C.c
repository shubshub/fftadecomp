#include "ffta.h"

void func_0800A0B4(void);
u32 func_0800A0B8(u32 mode, u32 enabled);
u8 func_08009E9C(u8 result);

u32 func_0800A06C(u32 mode)
{
    u32 result;

    func_0800A0B4();
    result = func_0800A0B8(mode, mode != 2);
    if (mode == 5 || mode == 6 || mode == 3) {
        result = func_08009E9C(result != 0);
        if (result == 2)
            return func_0800A0B8(7, 1);
    }
    return result;
}
