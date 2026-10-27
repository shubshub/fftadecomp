#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 value;
    u16 progress;
} TaskData;

extern TaskData *func_08005BFC(void *task);

/* 0804E9B0..0804E9C2: 18 bytes. */
void func_0804E9B0(void *task)
{
    TaskData *data = func_08005BFC(task);

    data->progress = 0;
    data->value = 0x40;
}
