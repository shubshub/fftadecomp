#include "ffta.h"

/* 0x0804CA00..0x0804CA44: 68 bytes / 26 instructions. */
typedef void (*BufferInitializer)(void *destination, u32 size);

extern u8 data_0201F550[];
extern u8 *data_0201F53C;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern u8 *func_080070C8(u8 *storage, u32 byte_count);

void func_0804CA00(void)
{
    u32 start = (u32)data_0201F550;
    u32 size;

    if (start & 3) {
        start &= ~3;
        start += 4;
    }
    size = 0x02040000 - start;
    g_callbacks_0836D4B8[0]((void *)start, size);
    data_0201F53C = func_080070C8((u8 *)start, size);
}
