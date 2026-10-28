#include "ffta.h"

/* 0x0800D9E0 .. 0x0800DA46: 102 bytes. */
extern u16 *func_0800C614(void *object);
extern void func_0800C64C(void *object);
extern void func_0814186C(const void *source, void *destination, u32 count);

void func_0800D9E0(void *object, u8 mode, u8 row, u8 index,
                   u8 count, const void *source)
{
    u16 *values = 0;

    switch (mode) {
    case 0:
        values = func_0800C614(object);
        break;
    case 1:
        values = func_0800C614(object) + row * 160;
        break;
    case 2:
        values = func_0800C614(object) + row * 160;
        break;
    }
    func_0814186C(source, values + index, count);
    func_0800C64C(object);
}
