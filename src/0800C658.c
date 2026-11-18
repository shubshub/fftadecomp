#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
} ScanlineTask;

void func_0800C658(ScanlineTask *task)
{
    task->flags &= ~(1 | 4);
}
