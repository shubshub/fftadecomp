#include "ffta.h"

/* 0x080D8AEC..0x080D8B18: 44 bytes. */
extern u32 func_08005BB0(const void *task);
extern void func_08005B58(void *task);

static inline u8 task_finished(const void *task)
{
    if (func_08005BB0(task)) {
        return 1;
    }
    return 0;
}

void *func_080D8AEC(void *task)
{
    if (task && task_finished(task)) {
        func_08005B58(task);
        return 0;
    }
    return task;
}
