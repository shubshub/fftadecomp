#include "ffta.h"

void *func_08005BFC(void *task);

void func_08006940(void *task, u8 value)
{
    u8 *payload = func_08005BFC(task);

    payload[8] = value;
}
