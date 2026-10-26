#include "ffta.h"

/* 0x080D7ABC..0x080D7AE8: 44 bytes. */
extern u32 func_08005BB0(u32 handle);
extern void func_08005B58(u32 handle);

static inline u8 is_handle_valid(u32 handle)
{
    if (func_08005BB0(handle) != 0)
        return 1;
    return 0;
}

u32 func_080D7ABC(u32 handle)
{
    if (handle != 0 && is_handle_valid(handle)) {
        func_08005B58(handle);
        return 0;
    }
    return handle;
}
