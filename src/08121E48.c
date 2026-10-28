#include "ffta.h"

/* 0x08121E48..0x08121E74: 44 bytes, 15 instructions. */
extern void *data_020159C4;
extern u8 *data_020159C8;
extern void *func_08022840(u32 size);
extern u8 *func_080070C8(u8 *storage, u32 byte_count);

void func_08121E48(void)
{
    u8 *storage = func_08022840(0x5000);
    void *owner = func_080070C8(storage, 0x5000);

    data_020159C4 = owner;
    data_020159C8 = storage;
}
