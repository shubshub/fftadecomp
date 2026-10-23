#include "ffta.h"

typedef u16 (*TaskCallback080099A4)(u32 context);

typedef struct {
    u32 context;
    TaskCallback080099A4 callback;
} Task080099A4;

u8 func_080099A4(u32 handle)
{
    Task080099A4 *tasks = (Task080099A4 *)0x03000890;
    u8 result = 0;

    if (tasks[handle].callback == 0)
        result = 1;

    return result;
}
