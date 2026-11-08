#include "ffta.h"

extern u32 func_08142AB0(u32, u32);
extern u32 func_08142B28(u32, u32);
extern const u8 data_08393AD0[];
extern void func_08001F34(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, u32, u32);

/* Complete 080684B4..08068548: 148 bytes, 68 instructions. */
void func_080684B4(u16 x, u16 y, u8 width, u16 value)
{
    u8 i;

    for (i = 0; i < width; i++) {
        u16 digit = func_08142B28(value, 10);

        value = func_08142AB0(value, 10);
        func_08001F34(data_08393AD0, (s16)x + (width - (i + 1)) * 8,
                      (s16)y, 0, 0, 0, 0, 0, digit * 2, 0, 0);
        if (value == 0)
            break;
    }
}
