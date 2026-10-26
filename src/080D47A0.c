#include "ffta.h"

struct TaskData080D47A0 {
    u8 unknown_00[7];
    u8 flags;
};

extern struct TaskData080D47A0 *func_08005BFC(void *task);

/* Complete [0x080D47A0, 0x080D47C6): 38 bytes, 18 instructions. */
void func_080D47A0(void *task, u8 enabled)
{
    struct TaskData080D47A0 *data = func_08005BFC(task);

    if (enabled)
        data->flags |= 1;
    else
        data->flags &= ~1;
}
