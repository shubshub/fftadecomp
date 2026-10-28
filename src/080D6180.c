#include "ffta.h"

struct TaskData080D6180 {
    u8 unknown_00[14];
    u8 flags;
};

extern struct TaskData080D6180 *func_08005BFC(void *task);

/* Complete [0x080D6180, 0x080D6192): 18 bytes, 8 instructions. */
void func_080D6180(void *task)
{
    struct TaskData080D6180 *data = func_08005BFC(task);

    data->flags |= 1;
}
