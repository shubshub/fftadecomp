#include "ffta.h"

extern unsigned char data_03000EE0[];
extern const unsigned char data_080000FC[];
extern const unsigned char data_0800023C[];
extern void func_080027E4(void *entries);
extern void *func_080023EC(void *buffer, u32 index, const void *source, u16 size);

/* 0800058C..080005CC: 64 bytes including the literal pool. */
void func_0800058C(void)
{
    func_080027E4(data_03000EE0);
    func_080023EC(data_03000EE0, 0, data_080000FC,
                 (u16)((u32)data_0800023C - (u32)data_080000FC + 32));
}
