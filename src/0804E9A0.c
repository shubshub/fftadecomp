#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 value;
} TaskData;

extern TaskData *func_08005BFC(void *task);

/* 0804E9A0..0804E9AE: 14 bytes. */
void func_0804E9A0(void *task)
{
    TaskData *data = func_08005BFC(task);

    data->value = 0x80;
}
