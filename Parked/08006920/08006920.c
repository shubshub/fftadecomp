#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct InterpolationDescriptor {
    u16 state;
    u8 unknown_02[2];
    const void *records;
    u8 unknown_08[0xC];
    u16 count;
    u8 unknown_16[6];
} InterpolationDescriptor;

u32 func_08006720(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_08006920(const void *records, u16 count, void *parent)
{
    InterpolationDescriptor descriptor;

    descriptor.records = records;
    descriptor.count = count;
    return func_08005B6C(func_08006720, 0xC, &descriptor, parent);
}
