#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} CompletionContext;

typedef struct {
    u16 state;
    u16 unknown_02;
    CompletionContext *context;
    u32 unknown_08[5];
} TaskDescriptor;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u32 func_0812BA08(void *task, void *descriptor, void *payload);
extern void *func_08121B8C(TaskCallback callback, u16 payload_size,
                          void *descriptor, void *parent);

void func_0812BD2C(CompletionContext *context)
{
    TaskDescriptor descriptor;

    context->complete = 0;
    descriptor.context = context;
    func_08121B8C(func_0812BA08, 0x44, &descriptor, 0);
}
