#include "ffta.h"

extern u16 *func_0800C614(void *object);
extern void func_0814186C(const void *source, void *destination, u32 count);
extern void func_0800C64C(void *object);

/* Complete [0x0800DA88, 0x0800DAB8): 48 bytes, 21 instructions. */
void func_0800DA88(void *object, s16 index, u8 count, const u16 *source)
{
    if (index < 160) {
        u16 *values = func_0800C614(object);

        values += index;
        func_0814186C(source, values, count);
        func_0800C64C(object);
    }
}
