#include "ffta.h"

typedef struct TaskManagerPrefix TaskManagerPrefix;
typedef struct {
    u8 unknown_00[0x20];
    TaskManagerPrefix *manager;
    u32 unknown_24;
    u8 *allocation;
} AllocationState;

extern AllocationState *data_0200F438;
extern void func_08005B0C(TaskManagerPrefix *manager, u8 *allocation);

/* 0802966C..08029688: 28 bytes. */
void func_0802966C(void)
{
    if (data_0200F438->allocation != 0)
        func_08005B0C(data_0200F438->manager, data_0200F438->allocation);
}
