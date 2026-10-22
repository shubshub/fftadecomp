#include "ffta.h"

typedef struct {
    u8 unknown_00[0x424];
    void *entries[0];
} PointerContainer;

typedef struct {
    PointerContainer *container;
    u8 unknown_04[2];
    u16 count;
    u8 kind;
} TaskPayload;

void *func_08005BFC(void *task);

void *func_0806514C(void *task)
{
    const TaskPayload *payload = func_08005BFC(task);
    u16 index = payload->count - 1;

    switch (payload->kind) {
    case 7:
        return payload->container->entries[(s16)index];
    default:
        return 0;
    }
}
