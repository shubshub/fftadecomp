#include "ffta.h"

/* 0x080D4938..0x080D4968: 48 bytes. */
extern void func_08005B58(u32 handle);

void func_080D4938(u32 *handles, u16 count)
{
    u16 i;

    for (i = 0; i < count; i++) {
        if (handles[i] != 0) {
            func_08005B58(handles[i]);
            handles[i] = 0;
        }
    }
}
