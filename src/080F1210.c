#include "ffta.h"

/* 0x080F1210..0x080F123C: 44 bytes, 20 instructions. */
extern u32 func_08005BB0(void *task);
extern void func_08005B58(void *task);

static inline u8 task_is_finished(void *task)
{
    if (func_08005BB0(task)) {
        return 1;
    }
    return 0;
}

void *func_080F1210(void *task)
{
    if (task && task_is_finished(task)) {
        func_08005B58(task);
        return 0;
    }
    return task;
}
