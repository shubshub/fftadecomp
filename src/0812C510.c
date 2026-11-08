#include "ffta.h"

typedef struct {
    u8 unknown00[6];
    u8 completed;
} Owner;

typedef struct {
    u16 phase;
    u16 unknown02;
    Owner *owner;
    u32 unknown08[5];
} Request;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u32 func_0812C2B8(void *task, void *descriptor, void *payload);
extern void *func_08121B8C(TaskCallback callback, u16 payload_size,
                          void *descriptor, void *parent);

void func_0812C510(Owner *owner)
{
    Request request;

    owner->completed = 0;
    request.owner = owner;
    func_08121B8C(func_0812C2B8, 0x5C, &request, 0);
}
