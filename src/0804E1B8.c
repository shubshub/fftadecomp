#include "ffta.h"

/* 0x0804E1B8..0x0804E1DE: 38 bytes / 15 instructions. */
struct MenuContext0804E1B8 {
    u8 unknown_00[8];
    void *manager;
};

extern struct MenuContext0804E1B8 *data_0201F548;
extern void func_08005A24(void *manager);

s32 func_0804E1B8(void)
{
    if (data_0201F548 == 0 || data_0201F548->manager == 0)
        return -1;
    func_08005A24(data_0201F548->manager);
    return 0;
}
