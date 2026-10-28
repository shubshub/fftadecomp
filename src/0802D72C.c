#include "ffta.h"

typedef struct {
    void *manager;
    void *allocation;
    void *first_task;
    void *second_task;
} TaskContext;

extern TaskContext *data_0200F440;

/* 0802D72C..0802D750: 36 bytes, 13 instructions, including literal pools. */
void *func_0802D72C(u8 first)
{
    if (first == 0)
        return data_0200F440->second_task;

    return data_0200F440->first_task;
}
