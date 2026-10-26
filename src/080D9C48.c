#include "ffta.h"

/* 0x080D9C48..0x080D9C56: 14 bytes, 6 instructions. */
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_080D9C48(const void *const *source, void *destination)
{
    func_0814186C(*source, destination, 0xA0);
}
