#include "ffta.h"

/* 0x080A8288..0x080A82C0: 56 bytes, including the literal pool. */
extern u8 data_0200F8A8[];

void func_080A1B58(void *context, void *object, s16 x, s16 y, s16 z, s8 mode);

void func_080A8288(void *object, s16 x, s16 y, s16 z, s8 mode)
{
    func_080A1B58(data_0200F8A8, object, x, y, z, mode);
}
