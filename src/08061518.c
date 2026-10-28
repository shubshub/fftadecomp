#include "ffta.h"

/* 0x08061518..0x08061564: 76 bytes. */
extern u8 data_030008B0[];
extern u8 data_03000990[];

extern void func_0802A2C0(u32 first, u32 second, u32 third, u32 fourth);
extern void func_0801174C(void *context, u32 kind, u8 index,
                          void *first, void *second, u32 count, u32 mode,
                          u32 width, u32 height, u32 size);

void func_08061518(void *context, u8 index)
{
    func_0802A2C0(0, 0, 0, 0);
    func_0801174C(context, 9, index, data_030008B0, data_03000990,
                  2, 1, 0x18, 0x10, 0x1C0);
}
