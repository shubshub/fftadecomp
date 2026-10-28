#include "ffta.h"

extern void *func_0800B2A4(u8 kind, u32 first, u32 second, u32 third, u32 fourth);
extern void *func_0800B394(u32 kind, u32 first, u32 second, u32 third, u32 fourth);
extern void func_0800BEDC(void *object, u8 mode);
extern void func_0800BED8(void *object, s16 value);

void *func_080D4C9C(u8 kind, u32 first, u32 second, u8 enabled, u16 value, u8 mode)
{
    void *object;

    if (enabled)
        object = func_0800B2A4(kind, first, second, 0, 0);
    else
        object = func_0800B394(0, first, second, 0, 0);
    func_0800BEDC(object, mode);
    func_0800BED8(object, (s16)value);
    return object;
}
