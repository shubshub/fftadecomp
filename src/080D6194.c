#include "ffta.h"

struct TaskData080D6194 {
    u8 unknown_00[14];
    u8 flags;
};

extern struct TaskData080D6194 *func_08005BFC(void *task);

/* Complete [0x080D6194, 0x080D61BA): 38 bytes, 18 instructions. */
void func_080D6194(void *task, u8 enabled)
{
    struct TaskData080D6194 *data = func_08005BFC(task);

    if (enabled)
        data->flags |= 2;
    else
        data->flags &= ~2;
}
