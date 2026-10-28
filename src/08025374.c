#include "ffta.h"

/* 0x08025374..0x080253B0: 60 bytes / 23 instructions. */
typedef struct {
    u8 unknown_00[0x20];
    void *manager;
    u8 *allocation;
} Context;

extern Context *data_0200F438;
extern void func_08005A24(void *manager);
extern void func_08005B18(void *manager);
extern void func_08005C34(void *manager);
extern void func_08022854(u8 *object);

void func_08025374(void)
{
    if (data_0200F438 != 0) {
        u8 *allocation = data_0200F438->allocation;

        func_08005A24(data_0200F438->manager);
        func_08005B18(data_0200F438->manager);
        func_08005C34(data_0200F438->manager);
        data_0200F438->manager = 0;
        func_08022854(allocation);
        data_0200F438 = 0;
    }
}
