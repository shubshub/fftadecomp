#include "ffta.h"

struct TaskData0804E1E0 {
    u8 unknown_00[6];
    s16 value;
};

extern struct TaskData0804E1E0 *func_08005BFC(void *task);

s16 func_0804E1E0(void *task)
{
    return func_08005BFC(task)->value;
}
