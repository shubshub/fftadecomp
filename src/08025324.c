#include "ffta.h"

struct Context08025324 {
    u8 unknown_00[0x20];
    void *manager;
    u8 *allocation;
    u8 unknown_28[0x460];
};

typedef void (*BufferInitializer08025324)(void *destination, u32 size);

extern struct Context08025324 *data_0200F438;
extern BufferInitializer08025324 const g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);
extern void *func_08005C14(void *storage, u32 size);

/* 0x08025324..0x08025374: 80 bytes, including literal pools. */
void func_08025324(u32 size)
{
    u8 *storage = func_08022840(size);

    data_0200F438 = (struct Context08025324 *)storage;
    g_callbacks_0836D4B8[0](storage, sizeof(*data_0200F438));
    data_0200F438->allocation = storage;
    storage += sizeof(*data_0200F438);
    data_0200F438->manager = func_08005C14(storage,
        size - sizeof(*data_0200F438));
}
