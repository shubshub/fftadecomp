#include "ffta.h"

/* 0x080C15C0..0x080C15DC: 28 bytes. */
typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer const g_callbacks_0836D4B8[];
extern u8 data_020156C4[];

void func_080C15C0(void)
{
    g_callbacks_0836D4B8[0](data_020156C4, 24);
}
