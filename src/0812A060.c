/* 0x0812A060, 36 bytes. Start the object task with a request descriptor. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 busy;
} Object0812A060;

typedef struct {
    u16 state;
    u16 unknown_02;
    Object0812A060 *object;
    u32 unknown_08[5];
} TaskRequest0812A060;

typedef u32 (*TaskCallback0812A060)(void *task, void *request, void *payload);

extern u32 func_081295C8(void *task, void *request, void *payload);
extern void *func_08121B8C(TaskCallback0812A060 callback, u16 payload_size,
                          void *request, void *parent);

void func_0812A060(Object0812A060 *object)
{
    TaskRequest0812A060 request;

    object->busy = 0;
    request.object = object;
    func_08121B8C(func_081295C8, 0x3D8, &request, 0);
}
