#include "ffta.h"

typedef u16 (*TaskCallback)(u32 argument);

typedef struct {
    u32 argument;
    TaskCallback callback;
} Task;

/* Target: 0x080098C4, 48 bytes including the required literal word. */
void func_080098C4(u8 outer_index, u8 *outer_flag)
{
    Task *tasks = (Task *)0x03000890;
    int index;

    for (index = 0; index < 4; index++) {
        if (tasks[index].callback != 0 &&
            tasks[index].callback(tasks[index].argument) != 0)
            tasks[index].callback = 0;
    }
}
