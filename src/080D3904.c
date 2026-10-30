#include "ffta.h"

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

/* 0x080D3904..0x080D3918: 20 bytes, including the global-pointer literal. */
void *func_080D3904(void)
{
    return (u8 *)func_08005BFC(data_020159C0) + 12;
}
