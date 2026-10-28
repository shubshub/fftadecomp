#include "ffta.h"

extern void *data_0200F434;
extern void *func_08007138(void *allocator, u32 size);

/* 08022840..08022854: 20 bytes. */
void *func_08022840(u32 size)
{
    return func_08007138(data_0200F434, size);
}
