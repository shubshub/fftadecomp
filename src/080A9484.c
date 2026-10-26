#include "ffta.h"

extern const u8 data_0839454C[];

extern void func_08001CF0(const void *data, s32 x, s32 y, u32 argument3,
                         u32 argument4, u32 argument5, u32 argument6,
                         u32 argument7, u32 argument8, u32 flags,
                         u32 argument10);

/* Complete [0x080A9484, 0x080A94B8): 52 bytes, 23 instructions. */
void func_080A9484(u32 unused, s16 x, s16 y, u8 flags)
{
    func_08001CF0(data_0839454C, x, y, 0, 0, 0, 0, 0, 0, flags, 0);
}
