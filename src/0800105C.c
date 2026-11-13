// 0800105C..08001194: 312 bytes, 123 instructions.
// Resets the double-buffered sprite lists: clears both buffer selectors and
// the per-buffer output pointers, fills every buffer with hidden OAM entries
// (y 168, x 248) and clears each buffer's 0x20- and 0x100-byte areas through
// the buffer-clear callback.
#include "ffta.h"

typedef unsigned long long u64;
typedef void (*BufferInitializer)(void *destination, u32 size);

extern u8 data_03000028;
extern u8 data_03002F58;
extern s32 data_03002C50[2];
extern u32 data_03002F60[2];
extern s32 data_03000020[2];
extern u32 data_03003168[2];
extern u64 data_03002C58[2][0x30];
extern u64 data_03002F68[2][0x20];
extern u64 data_03000030[2][0x80];
extern u64 data_03003170[2][0x10];
extern u8 data_03003270[0x40];
extern u8 data_030032B0[0x200];
extern BufferInitializer g_callbacks_0836D4B8[];
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer callback);

#define HIDDEN_OAM_ENTRY 0x00F800A8

static inline void HideEntries(u64 *entry, s32 count)
{
    for (; count > 0; count--)
        *entry++ = HIDDEN_OAM_ENTRY;
}

void func_0800105C(void)
{
    data_03000028 = data_03002F58 = 0;
    data_03002C50[1] = 0;
    data_03002C50[0] = 0;
    data_03002F60[1] = 0;
    data_03002F60[0] = 0;
    data_03000020[1] = 0;
    data_03000020[0] = 0;
    data_03003168[1] = 0;
    data_03003168[0] = 0;

    HideEntries(data_03002C58[0], 0x30);
    HideEntries(data_03002C58[1], 0x30);
    HideEntries(data_03002F68[0], 0x20);
    HideEntries(data_03002F68[1], 0x20);
    HideEntries(data_03000030[0], 0x80);
    HideEntries(data_03000030[1], 0x80);
    HideEntries(data_03003170[0], 0x10);
    HideEntries(data_03003170[1], 0x10);

    func_0814224C(data_03003270, sizeof(data_03003270), g_callbacks_0836D4B8[0]);
    func_0814224C(data_030032B0, sizeof(data_030032B0), g_callbacks_0836D4B8[0]);
}
