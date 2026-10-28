#include "ffta.h"

/* 0x0805F414..0x0805F44C: 56 bytes / 21 instructions. */
typedef struct {
    void *manager;
    u8 *allocation;
} Context;

extern Context *data_0200F44C;
extern void func_08005A24(void *manager);
extern void func_08005B18(void *manager);
extern void func_08005C34(void *manager);
extern void func_08022854(u8 *object);

void func_0805F414(void)
{
    if (data_0200F44C != 0) {
        u8 *allocation = data_0200F44C->allocation;

        func_08005A24(data_0200F44C->manager);
        func_08005B18(data_0200F44C->manager);
        func_08005C34(data_0200F44C->manager);
        func_08022854(allocation);
        data_0200F44C = 0;
    }
}
