#include "ffta.h"

typedef struct {
    u8 unknown_00[0x13];
    u8 value;
} TaskData;

extern TaskData *func_08005BFC(void *task);
extern void func_08005BA8(void *task, u16 state);

/* 0802B894..0802B8CA: 54 bytes. */
void func_0802B894(void *task, u8 mode, u8 value)
{
    TaskData *data = func_08005BFC(task);

    if (mode != 0) {
        func_08005BA8(task, 0x109);
    } else {
        data->value = value;
        func_08005BA8(task, 0x108);
    }
}
