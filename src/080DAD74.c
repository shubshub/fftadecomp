#include "ffta.h"

/* 0x080DAD74..0x080DAD92: 30 bytes, 12 instructions. */
typedef struct {
    u8 unknown_00[4];
    void *object;
} TaskRecord;

extern TaskRecord *func_08005BFC(void *task);
extern void *func_0800C614(void *object);
extern void func_080DA77C(u32 value, u32 mode, void *output);

void func_080DAD74(void *task, u32 value)
{
    void *output = func_0800C614(func_08005BFC(task)->object);
    func_080DA77C(value, 3, output);
}
