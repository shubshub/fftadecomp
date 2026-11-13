#include "ffta.h"

/* Complete [0x08096ED4, 0x08096F3C): 104 bytes, 35 instructions.
 * 30 b5 34 20 8b f7 d2 f8 05 1c 01 20 b2 f0 2c f9
 * 04 1c 64 19 0f 48 24 18 20 20 40 42 04 40 0e 4d
 * 84 20 c0 00 24 18 20 1c 8b f7 a0 fc 28 60 0b 49
 * 0a 68 21 1c ab f0 a0 f9 28 68 21 1c 70 f7 da f8
 * 07 49 08 60 00 f0 72 f8 06 49 08 60 30 bc 01 bc
 * 00 47 00 00 68 16 00 00 b8 f4 00 02 b8 d4 36 08
 * b4 f4 00 02 b0 f4 00 02
 */

typedef void (*BufferInitializer)(void *destination, u32 size);

extern u8 *data_0200F4B8;
extern void *data_0200F4B4;
extern void *data_0200F4B0;
extern BufferInitializer const g_callbacks_0836D4B8[];

extern u32 func_08022080(u32 count);
extern u32 func_0814913C(u8 count);
extern void *func_08022840(u32 size);
extern void *func_080070C8(void *storage, u32 size);
extern void *func_08097000(void *allocator);

void func_08096ED4(void)
{
    u32 context_size = func_08022080(0x34);
    u32 size = func_0814913C(1);

    size += context_size;
    size += 0x1668;
    size &= ~0x1F;
    data_0200F4B8 = func_08022840(size += 0x420);
    g_callbacks_0836D4B8[0](data_0200F4B8, size);
    data_0200F4B4 = func_080070C8(data_0200F4B8, size);
    data_0200F4B0 = func_08097000(data_0200F4B4);
}
