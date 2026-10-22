#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u32 value_04;
    u32 value_08;
    u8 unknown_0C[0x10];
} TaskDescriptor;

typedef struct {
    void *manager;
} TaskContext;

typedef void (*TaskCallback)(void *task, void *descriptor, void *payload);

void *func_08005954(void *manager, TaskCallback callback, u32 payload_bytes,
                  const TaskDescriptor *descriptor, void *parent);

void *func_0806517C(u8 selector, u32 value_04, u32 value_08)
{
    TaskDescriptor descriptor;

    descriptor.value_04 = value_04;
    descriptor.value_08 = value_08;
    if (selector == 4)
        return func_08005954((*(TaskContext **)0x0200F454)->manager,
                             (TaskCallback)0x08065EF5, 0x468, &descriptor, 0);
    return func_08005954((*(TaskContext **)0x0200F454)->manager,
                         (TaskCallback)0x08065D01, 0x1098, &descriptor, 0);
}
