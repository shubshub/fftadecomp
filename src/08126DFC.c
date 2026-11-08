#include "ffta.h"

/* Target: 56 bytes. */
typedef struct Object {
    u8 unknown_00[6];
    u8 ready;
} Object;

typedef struct Request {
    u32 unknown_00;
    Object *object;
    u32 unknown_08[3];
    u16 first;
    u16 second;
    u16 third;
    u16 unknown_1A;
} Request;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_08126BFC(void *task, void *descriptor, void *payload);
void *func_08121B8C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void func_08126DFC(Object *object, u8 first, u8 second, u8 third)
{
    Request request;

    object->ready = 0;
    request.object = object;
    request.first = first;
    request.second = second;
    request.third = third;
    func_08121B8C(func_08126BFC, 12, &request, 0);
}
