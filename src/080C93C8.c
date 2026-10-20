#include "ffta.h"

void func_080C9574(u16 bitIndex, u16 enabled);
void func_080C8C24(void *object, u8 selector);

void func_080C93C8(void *object, u8 selector)
{
    func_080C9574(0x3E, 1);
    func_080C8C24(object, selector);
    func_080C9574(0x3E, 0);
}
