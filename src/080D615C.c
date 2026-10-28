#include "ffta.h"

struct TaskData080D615C {
    u16 first;
    u16 second;
    u16 third;
};

extern struct TaskData080D615C *func_08005BFC(void *task);

/* Complete [0x080D615C, 0x080D6180): 36 bytes, 17 instructions. */
void func_080D615C(void *task, u16 first, u16 second, u16 third)
{
    struct TaskData080D615C *data = func_08005BFC(task);

    data->first = first;
    data->second = second;
    data->third = third;
}
