#include "ffta.h"

extern u8 data_02003CB0[];
extern const u8 data_083AEEA4[];
extern u8 data_06008A40[];
extern void func_0800543C(void *, const void *);
extern void func_0814186C(const void *, void *, u32);

/* 0x0803131C..0x08031348: 44 bytes, 13 instructions. */
void func_0803131C(void)
{
    u8 *buffer = data_02003CB0;

    func_0800543C(buffer, data_083AEEA4);
    func_0814186C(buffer, data_06008A40, 0x5a0);
}
