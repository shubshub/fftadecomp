#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct {
    void *manager;
} State;

extern State *data_020159CC;
extern void *func_08005954(void *manager, TaskCallback callback,
                          u16 payload_size, void *descriptor, void *parent);

/* Complete [0x08121B8C, 0x08121BB8): 44 bytes, 19 instructions. */
void *func_08121B8C(TaskCallback callback, u16 payload_size,
                   void *descriptor, void *parent)
{
    return func_08005954(data_020159CC->manager, callback, payload_size,
                         descriptor, parent);
}
