#include "ffta.h"

extern u8 data_02003CB0[];
extern const u8 data_083AD5F8[];
extern u8 data_06008A40[];
extern void func_0800543C(void *, const void *);
extern void func_0814186C(const void *, void *, u32);

/* 0x080312F0..0x0803131C, complete 44-byte target:
 * 10 B5 07 4C 07 49 20 1C D4 F7 A0 F8 06 49 C6 22
 * D2 00 20 1C 10 F1 B2 FA 10 BC 01 BC 00 47 00 00
 * B0 3C 00 02 F8 D5 3A 08 40 8A 00 06
 */
void func_080312F0(void)
{
    u8 *buffer = data_02003CB0;

    func_0800543C(buffer, data_083AD5F8);
    func_0814186C(buffer, data_06008A40, 0x630);
}
