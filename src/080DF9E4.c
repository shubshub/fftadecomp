#include "ffta.h"

/* Target: 0x080DF9E4, complete 74-byte Thumb function. */
typedef struct ObjectState ObjectState;

typedef struct TaskDescriptor {
    u16 state;
    u16 unknown_02;
    ObjectState *object;
    u8 unknown_08[12];
    u16 delay;
    u16 flags;
    u32 unknown_18;
} TaskDescriptor;

typedef u32 (*TaskCallback)(void *task, TaskDescriptor *descriptor, void *payload);

u8 func_080DD580(const ObjectState *object);
u8 func_080DD598(const ObjectState *object);
u32 func_080DF080(void *task, TaskDescriptor *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                    TaskDescriptor *descriptor, void *parent);

void *func_080DF9E4(ObjectState *object, u16 flags, u16 delay, void *parent)
{
    if (func_080DD580(object) && func_080DD598(object)) {
        TaskDescriptor descriptor;

        descriptor.object = object;
        descriptor.delay = delay;
        descriptor.flags = flags;
        return func_08005B6C(func_080DF080, 8, &descriptor, parent);
    }
    return 0;
}
