#include "ffta.h"

/* 0x08000A48..0x08000A98: 80 bytes / 28 instructions. */
typedef void (*BufferInitializer)(void *destination, u32 size);

extern u16 data_03002BC0[];
extern u32 data_03002BCC;
extern u8 data_03002BD0[0x40];
extern u8 data_03002C10[0x40];
extern BufferInitializer g_callbacks_0836D4B8[];

void func_08000A48(void)
{
    u32 index;

    for (index = 0; index < 4; index++)
        data_03002BC0[index] = 0;
    data_03002BC0[1] = 1;
    data_03002BCC = 0;
    g_callbacks_0836D4B8[0](data_03002BD0, sizeof(data_03002BD0));
    g_callbacks_0836D4B8[0](data_03002C10, sizeof(data_03002C10));
}
