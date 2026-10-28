#include "ffta.h"

/* Complete [0x0813C0D8, 0x0813C0EC): 20 bytes, 7 instructions. */
extern void *data_0200F3BC;
extern void func_08007170(void *owner, u8 *object);

void func_0813C0D8(u8 *object)
{
    func_08007170(data_0200F3BC, object);
}
