#include "ffta.h"

typedef struct {
    void *manager;
    void *allocation;
    void *first_task;
    void *second_task;
} TaskContext;

extern TaskContext *data_0200F440;
extern void func_08005A24(void *manager);

/* 0802B6F0..0802B70C: 28 bytes, 11 instructions. */
void func_0802B6F0(void)
{
    TaskContext *context = data_0200F440;

    if (context != 0 && context->manager != 0)
        func_08005A24(context->manager);
}
