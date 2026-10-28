#include "ffta.h"

struct TaskData080D3958 {
    u32 unknown_00[2];
    u32 value;
};

extern void *data_020159C0;
extern struct TaskData080D3958 *func_08005BFC(void *task);

/* Complete [0x080D3958, 0x080D3970): 24 bytes, 9 instructions. */
void func_080D3958(u32 value)
{
    func_08005BFC(data_020159C0)->value = value;
}
