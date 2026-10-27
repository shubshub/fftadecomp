#include "ffta.h"

/* 0x0800058C..0x080005CC: 64 bytes / 23 instructions. */
extern u8 data_03000EE0[];
extern const u8 data_080000FC[];
extern const u8 data_0800023C[];

extern void func_080027E4(void *destination);
extern void func_080023EC(void *destination, u32 mode,
                         const void *source, u16 size);

void func_0800058C(void)
{
    func_080027E4(data_03000EE0);
    func_080023EC(data_03000EE0, 0, data_080000FC,
                  (u16)((u32)data_0800023C - (u32)data_080000FC + 0x20));
}
