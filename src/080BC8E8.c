#include "ffta.h"

/* 0x080BC8E8..0x080BC900: 24 bytes, 9 instructions and a literal pool. */
extern u8 data_02010130[];
extern void func_080BB5C4(void *state, void *object, u8 x, u8 y);

void func_080BC8E8(void *context, void *object, u8 x, u8 y)
{
    func_080BB5C4(data_02010130, object, x, y);
}
