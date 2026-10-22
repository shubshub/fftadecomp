#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 size;
    u8 unknown_06[2];
    void *buffer;
} TaskPayload;

void *func_08005BFC(void *task);
void func_08005B40(void *object);
void *func_08005B28(u32 byte_count);

void func_080068AC(void *task, u16 size)
{
    TaskPayload *payload = func_08005BFC(task);

    if (payload->size != size) {
        func_08005B40(payload->buffer);
        payload->size = size;
        payload->buffer = func_08005B28(payload->size);
    }
}
