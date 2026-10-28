#include "ffta.h"

/* 0x0805D91C..0x0805D948: 44 bytes. */
extern const u8 data_08393890[];
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                        u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                        u32 value, u8 mode, const void *transform);

void func_0805D91C(void)
{
    func_08001F34(data_08393890, 40, 7, 0, 0, 0, 0, 0, 0, 0, 0);
}
