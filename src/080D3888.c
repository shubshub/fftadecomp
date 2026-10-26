#include "ffta.h"

/* 0x080D3888..0x080D38B4: 44 bytes. */
extern u32 data_0200F430;
extern u8 func_08005BB0(u32 handle);
extern void func_080058A4(u32 parent, u32 handle);

u32 func_080D3888(u32 handle)
{
    if (handle != 0 && func_08005BB0(handle)) {
        func_080058A4(data_0200F430, handle);
        return 0;
    }
    return handle;
}
