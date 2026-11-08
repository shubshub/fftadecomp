/* 0x080068D4: complete 48-byte caller, including callback literal at 0x08006900. */
#include "ffta.h"

typedef struct BatchDescriptor {
    u16 state;
    u8 unknown_02[2];
    void *items;
    u8 unknown_08[0xC];
    u16 count;
    u8 unknown_16[6];
} BatchDescriptor;

typedef struct BatchPayload BatchPayload;
typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_0800620C(void *task, BatchDescriptor *descriptor, BatchPayload *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080068D4(void *items, u16 count, void *parent)
{
    BatchDescriptor descriptor;
    u16 items_size = count << 4;

    descriptor.items = items;
    descriptor.count = count;
    return func_08005B6C((TaskCallback)func_0800620C,
                         items_size + 0x40, &descriptor, parent);
}
