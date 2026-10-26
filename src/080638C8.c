#include "ffta.h"

/* Complete [0x080638C8, 0x08063904): 60 bytes, 27 instructions. */
extern ScriptState *data_0200F450;
extern void func_0802A2C0(s32, s32, s32, s32);

void func_080638C8(void)
{
    data_0200F450->unknown_4d = 7;
    func_0802A2C0(0, 0, 0, 0);
    data_0200F450->current = 0x20;
    data_0200F450->entries[data_0200F450->count++] = 0x20;
    data_0200F450->current = 0x31;
}
