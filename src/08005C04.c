#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct {
    TaskCallback callback;
} TaskHeader;

u32 func_08005C04(void *task, void *descriptor)
{
    TaskHeader *header = task;

    return header->callback(task, descriptor, (u8 *)task + 0x18);
}
