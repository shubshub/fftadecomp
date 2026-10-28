#include "ffta.h"

struct TaskData080D9B38 {
    u8 state;
};

extern struct TaskData080D9B38 *func_08005BFC(void *task);

/* Complete [0x080D9B38, 0x080D9B46): 14 bytes, 6 instructions. */
void func_080D9B38(void *task)
{
    func_08005BFC(task)->state = 1;
}
