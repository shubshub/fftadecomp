#include "ffta.h"

typedef void (*BufferInitializer080A87B4)(void *destination, u32 size);

extern void *func_08022840(u32 size);
extern BufferInitializer080A87B4 const g_callbacks_0836D4B8[];

/* Complete [0x080A87B4, 0x080A87DC): 40 bytes, 15 instructions. */
void *func_080A87B4(void)
{
    u32 size = 0x2C4;
    void *allocation = func_08022840(size);

    g_callbacks_0836D4B8[0](allocation, size);
    return allocation;
}
