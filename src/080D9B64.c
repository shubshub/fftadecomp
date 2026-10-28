#include "ffta.h"

typedef struct {
    u8 state;
} TaskData;

extern u32 func_08005BB0(const void *task);
extern void func_08005B58(void *task);
extern TaskData *func_08005BFC(void *task);

static inline u8 is_finished(const void *task)
{
    return func_08005BB0(task) != 0;
}

/* 080D9B64..080D9B98: 52 bytes. */
void *func_080D9B64(void *task)
{
    if (task != 0) {
        TaskData *data;

        if (is_finished(task)) {
            func_08005B58(task);
            return 0;
        }
        data = func_08005BFC(task);
        data->state = 1;
    }
    return task;
}
