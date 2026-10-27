#include "ffta.h"

typedef struct {
    u32 unknown_00;
    void *object;
} TaskData;

extern TaskData *func_08005BFC(void *task);
extern void func_0800DAB8(void *object, s16 start, u8 count, u8 first, u8 second);

/* 080D9ADC..080D9B06: 42 bytes. */
void func_080D9ADC(void *task, u8 first, u8 second)
{
    TaskData *data = func_08005BFC(task);

    func_0800DAB8(data->object, 0, 160, first, second);
}
