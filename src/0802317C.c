#include "ffta.h"

extern const u8 data_083A9CA4[];
extern u8 data_02003CB0[];
extern u8 data_06008A40[];

extern void func_08005318(const void *source, void *destination,
                          u32 index, u32 flag);
extern void func_08141868(const void *source, void *destination, u32 control);

/* 0x0802317C..0x080231AC: 48 complete bytes, including alignment and literals. */
void func_0802317C(void)
{
    func_08005318(data_083A9CA4, data_02003CB0, 0, 0);
    func_08141868(data_02003CB0, data_06008A40, 0x210);
}
