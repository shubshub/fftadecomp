#include "ffta.h"

/* 0x080D4774..0x080D47A0: 44 bytes, 20 instructions. */
extern u32 func_08005BB0(void *task);
extern void func_08005B58(void *task);

static inline u8 task_finished(void *task)
{
    if (func_08005BB0(task)) {
        return 1;
    }
    return 0;
}

void *func_080D4774(void *task)
{
    if (task && task_finished(task)) {
        func_08005B58(task);
        return 0;
    }
    return task;
}
