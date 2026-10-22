#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    s16 value_06;
} TaskValue;

void *func_08005BFC(void *task);

s16 func_08065050(const void *object)
{
    const TaskValue *payload = func_08005BFC((void *)object);

    return payload->value_06;
}
