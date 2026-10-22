#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 first;
    u16 second;
} TaskPayload;

void *func_08005BFC(void *task);

void func_08006904(void *task, u16 first, u16 second)
{
    TaskPayload *payload = func_08005BFC(task);

    payload->first = first;
    payload->second = second;
}
