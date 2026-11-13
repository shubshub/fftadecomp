// func_08001194: 0x08001194-0x08001244, 176 bytes, 65 instructions
// (including the ten-word literal pool at 0x0800121C).
#include "ffta.h"

typedef unsigned long long u64;
typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer const g_callbacks_0836D4B8[];
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer callback);

extern u8 data_03000028;
extern u8 data_03003270[][0x20];
extern u8 data_030032B0[][0x100];
extern u64 data_03002C58[][48];
extern s32 data_03002C50[];
extern u64 data_03000030[][128];
extern s32 data_03000020[];

static inline void HideEntries(u64 *entry, s32 count)
{
    for (; count > 0; count--)
        *entry++ = 0x00F800A8;
}

void func_08001194(void)
{
    BufferInitializer const *callbacks = g_callbacks_0836D4B8;

    func_0814224C(data_03003270[data_03000028], 0x20, callbacks[0]);
    func_0814224C(data_030032B0[data_03000028], 0x100, callbacks[0]);

    HideEntries(data_03002C58[data_03000028], data_03002C50[data_03000028]);
    HideEntries(data_03000030[data_03000028], data_03000020[data_03000028]);

    data_03002C50[data_03000028] = data_03000020[data_03000028] = 0;
}
