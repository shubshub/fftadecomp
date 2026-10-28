#include "ffta.h"

extern void func_080975DC(void *object, u16 identifier, s8 value, u8 mode);
extern void func_08097704(void *object, u16 identifier, s8 value);

/* 0x0809A2AC..0x0809A2D8: 44 bytes, 20 instructions. */
void func_0809A2AC(void *object, u16 identifier, s8 value, u8 mode)
{
    func_080975DC(object, identifier, value, mode);
    func_08097704(object, identifier, value);
}
