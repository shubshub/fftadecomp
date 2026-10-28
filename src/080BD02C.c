#include "ffta.h"

/* 0x080BD02C..0x080BD054: 40 bytes / 14 instructions. */
typedef void (*BufferInitializer)(void *destination, u32 size);

extern void *data_020101F0;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);

void func_080BD02C(void)
{
    void **state = &data_020101F0;

    *state = func_08022840(0x218);
    g_callbacks_0836D4B8[0](*state, 0x218);
}
