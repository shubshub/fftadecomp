#include "ffta.h"

/* 0x081380A8..0x081380B8: 16 bytes, 7 instructions. */
extern void func_08138014(s32 layer, s32 alternate, s32 screens);

void func_081380A8(void)
{
    func_08138014(0, 0, 2);
}
