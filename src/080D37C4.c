#include "ffta.h"

/* 0x080D37C4..0x080D37F8: 52 bytes. */
extern u32 data_020159C0;
extern u32 data_0200F430;
extern u32 func_08005BB0(u32 handle);
extern void func_080058A4(u32 parent, u32 handle);

u8 func_080D37C4(void)
{
    if (data_020159C0 != 0) {
        if (func_08005BB0(data_020159C0)) {
            func_080058A4(data_0200F430, data_020159C0);
            data_020159C0 = 0;
        }
        return 0;
    }
    return 1;
}
