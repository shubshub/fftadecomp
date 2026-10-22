#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 kind;
    u8 unknown_09[7];
    void *task;
} TaskPayload;

typedef struct {
    u16 event;
    u8 unknown_02[26];
} TaskDescriptor;

void *func_08005BFC(void *task);
u32 func_08005C04(void *task, void *descriptor);

void func_080651C8(void *task)
{
    TaskPayload *payload = func_08005BFC(task);
    TaskDescriptor descriptor;

    if (payload->kind == 7)
        descriptor.event = 0x103;
    else
        descriptor.event = 0x106;

    func_08005C04(payload->task, &descriptor);
}
