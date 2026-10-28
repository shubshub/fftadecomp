#include "ffta.h"

/* Target: complete [0x080DAE44, 0x080DAE70), 44 bytes. */
extern u32 func_08005BB0(const void *task);
extern void func_08005B58(void *task);

static inline u8 task_finished(const void *task)
{
    if (func_08005BB0(task))
        return 1;
    return 0;
}

void *func_080DAE44(void *task)
{
    if (task != 0 && task_finished(task))
    {
        func_08005B58(task);
        return 0;
    }
    return task;
}
