#include "ffta.h"

struct TaskData080D3970 {
    u16 unknown_00;
    u16 flags;
};

extern void *data_020159C0;
extern struct TaskData080D3970 *func_08005BFC(void *task);

/* Complete [0x080D3970, 0x080D3992): 34 bytes, 14 instructions. */
u8 func_080D3970(void)
{
    if (func_08005BFC(data_020159C0)->flags & 1)
        return 1;
    return 0;
}
