#include "ffta.h"

typedef struct TaskPayload {
    u8 unknown_00[0x0A];
    u16 field_0a;
} TaskPayload;

void *func_08005BFC(void *task);
void func_08005BA8(void *task, u16 value);

void func_08006954(void *task)
{
    TaskPayload *payload = func_08005BFC(task);

    payload->field_0a = 0;
    func_08005BA8(task, 0x100);
}
