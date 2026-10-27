#include "ffta.h"

/* 0x0800DA48..0x0800DA86: 62 bytes / 29 instructions. */
struct Object0800DA48;

extern void *func_0800C614(const struct Object0800DA48 *object);

u8 *func_0800DA48(const struct Object0800DA48 *object, u8 mode, u8 index)
{
    u8 *data = 0;

    switch (mode) {
    case 0:
        data = func_0800C614(object);
        break;
    case 1:
        data = (u8 *)func_0800C614(object) + index * 0x140;
        break;
    case 2:
        data = (u8 *)func_0800C614(object) + index * 0x140;
        break;
    }
    return data;
}
