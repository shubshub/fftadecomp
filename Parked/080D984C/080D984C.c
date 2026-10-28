#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u8 first_pair[2];
    u8 second_pair[2];
} TaskData;

extern TaskData *func_08005BFC(void *task);

/* 080D984C..080D987A: 46 bytes. */
void func_080D984C(void *task, u8 selector, u8 first, u8 second)
{
    TaskData *data = func_08005BFC(task);
    u8 *output;

    switch (selector) {
    case 0:
        output = data->first_pair;
        break;
    default:
        output = data->second_pair;
        break;
    }
    *output++ = first;
    *output = second;
}
