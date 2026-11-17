// 0x08126E34: submit a request built from two actor records.
// Target span [0x08126E34,0x08126EA4), 112 bytes.
#include "ffta.h"

typedef struct Actor {
    u8 unknown_00[0xF6];
    u8 first;
    u8 second;
    u8 fallback;
} Actor;

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
    u16 unknown_18[2];
} Request;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_08126BFC(void *task, void *descriptor, void *payload);
Actor *func_08125578(u8 index);
u8 func_08124ACC(u8, u8, u8, u8);
void *func_08121B8C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void func_08126E34(Object *object, u8 a, u8 b)
{
    Request request;
    Actor *x;
    Actor *y;
    u8 r;

    object->ready = 0;
    request.object = object;
    request.first = a;
    x = func_08125578(a);
    y = func_08125578(b);
    r = func_08124ACC(x->first, x->second, y->first, y->second);
    if (r == 0xFF)
        request.second = x->fallback;
    else
        request.second = r;
    func_08121B8C(func_08126BFC, 12, &request, 0);
}
