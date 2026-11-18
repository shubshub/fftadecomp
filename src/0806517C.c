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

typedef u32 (*TaskCallback)(void *task, TaskDescriptor *descriptor, void *payload);

extern TaskContext *data_0200F454;
extern u32 func_08065EF4(void *, TaskDescriptor *, void *);
extern u32 func_08065D00(void *, TaskDescriptor *, void *);

void *func_08005954(void *manager, TaskCallback callback, u16 payload_bytes,
                  const TaskDescriptor *descriptor, void *parent);

/* Complete [0x0806517C, 0x080651C8): 76 bytes. */
void *func_0806517C(u8 selector, u32 value_04, u32 value_08)
{
    TaskDescriptor descriptor;

    descriptor.value_04 = value_04;
    descriptor.value_08 = value_08;
    if (selector == 4)
        return func_08005954(data_0200F454->manager,
                             func_08065EF4, 0x468, &descriptor, 0);
    return func_08005954(data_0200F454->manager,
                         func_08065D00, 0x1098, &descriptor, 0);
}
