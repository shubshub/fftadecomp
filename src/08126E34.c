#include "ffta.h"

/* Complete [0x08126E34, 0x08126EA4): 112 bytes, 49 instructions and one
 * callback literal.  Queues func_08126BFC to turn scene record `first`
 * toward the facing func_08124ACC gives from it to record `second`. */
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

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xCC];
    u8 x;
    u8 y;
    u8 facing;
    u8 previousX;
    u8 previousY;
    u8 unknown_FB[0xD];
} SceneRecord;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_08126BFC(void *task, void *descriptor, void *payload);
SceneRecord *func_08125578(u8 selector);
u8 func_08124ACC(u8 start_x, u8 start_y, u8 end_x, u8 end_y);
void *func_08121B8C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void func_08126E34(Object *object, u8 first, u8 second)
{
    Request request;
    SceneRecord *actor;
    SceneRecord *target;
    u8 facing;

    object->ready = 0;
    request.object = object;
    request.first = first;
    actor = func_08125578(first);
    target = func_08125578(second);
    facing = func_08124ACC(actor->x, actor->y, target->x, target->y);
    if (facing == 0xFF)
        request.second = actor->facing;
    else
        request.second = facing;
    func_08121B8C(func_08126BFC, 12, &request, 0);
}
