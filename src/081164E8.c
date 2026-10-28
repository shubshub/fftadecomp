#include "ffta.h"

/* Target: complete [0x081164E8, 0x08116514), 44 bytes. */
extern u32 func_08005BB0(const void *task);
extern void func_08005B58(void *task);

static inline u8 task_is_finished(const void *task)
{
    if (func_08005BB0(task))
        return 1;
    return 0;
}

void *func_081164E8(void *task)
{
    if (task != 0) {
        if (task_is_finished(task)) {
            func_08005B58(task);
            return 0;
        }
    }
    return task;
}
