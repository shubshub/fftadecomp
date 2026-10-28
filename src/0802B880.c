#include "ffta.h"

struct TaskData0802B880 {
    u8 unknown_00[0x12];
    u8 mode;
};

extern struct TaskData0802B880 *func_08005BFC(void *task);

u8 func_0802B880(void *task)
{
    u8 mode;

    if (task)
        mode = func_08005BFC(task)->mode;
    else
        mode = 3;
    return mode;
}
