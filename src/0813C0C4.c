#include "ffta.h"

/* 0x0813C0C4..0x0813C0D8: 20 bytes, 7 instructions. */
extern void *data_0200F3BC;
extern void *func_08007138(void *owner, u32 bytes);

void *func_0813C0C4(u32 bytes)
{
    return func_08007138(data_0200F3BC, bytes);
}
