#include "ffta.h"

struct TaskData080D9B08 {
    u32 unknown_00;
    void *object;
};

extern struct TaskData080D9B08 *func_08005BFC(void *task);
extern u32 func_0800C614(void *object);

/* Complete [0x080D9B08, 0x080D9B18): 16 bytes, 6 instructions. */
u32 func_080D9B08(void *task)
{
    return func_0800C614(func_08005BFC(task)->object);
}
