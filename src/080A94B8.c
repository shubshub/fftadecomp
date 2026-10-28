#include "ffta.h"

typedef void (*BufferInitializer080A94B8)(void *destination, u32 size);

extern BufferInitializer080A94B8 const g_callbacks_0836D4B8[];
extern u8 data_0200FFC8[0x84];

/* Complete [0x080A94B8, 0x080A94D4): 28 bytes, 8 instructions. */
void func_080A94B8(void)
{
    g_callbacks_0836D4B8[0](data_0200FFC8, sizeof(data_0200FFC8));
}
