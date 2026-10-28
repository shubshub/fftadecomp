#include "ffta.h"

/* 0x080EEF6C .. 0x080EEF98: 44 bytes. */
extern int func_08005BB0(const void *);
extern void func_08005B58(void *);

static inline u8 task_finished(const void *task)
{
    if (func_08005BB0(task))
        return 1;
    return 0;
}

void *func_080EEF6C(void *task)
{
    void *result;

    if (task && task_finished(task)) {
        func_08005B58(task);
        result = 0;
    } else {
        result = task;
    }
    return result;
}
