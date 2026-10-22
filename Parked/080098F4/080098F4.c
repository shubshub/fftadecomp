#include "ffta.h"

typedef u16 (*TaskCallback080098F4)(u32 context);

typedef struct {
    u32 context;
    TaskCallback080098F4 callback;
} Task080098F4;

u8 func_080098F4(TaskCallback080098F4 callback, u32 context)
{
    Task080098F4 *task = (Task080098F4 *)0x03000890;
    s32 index;

    for (index = 0; index < 4; index++, task++) {
        if (!task->callback) {
            task->callback = callback;
            task->context = context;
            return index;
        }
    }

    return 0;
}
