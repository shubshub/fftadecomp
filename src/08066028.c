#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 value_04;
    u16 value_06;
} TaskPayload;

void *func_08005BFC(void *task);

void func_08066028(void *task)
{
    TaskPayload *payload = func_08005BFC(task);

    payload->value_06 = 0;
    payload->value_04 = 0x40;
}
