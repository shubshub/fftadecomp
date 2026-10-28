#include "ffta.h"

struct TaskData080DF950 {
    u8 unknown_00[0x0C];
    u16 value;
};

extern struct TaskData080DF950 *func_08005BFC(void *task);

/* Complete [0x080DF950, 0x080DF962): 18 bytes, 8 instructions. */
void func_080DF950(void *task, u16 value)
{
    func_08005BFC(task)->value = value;
}
