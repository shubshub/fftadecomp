#include "ffta.h"

/* Target: 0x0800A1D0..0x0800A1E4, 00b548788a7812021043c978bff0f0f901bc0047. */
void func_080C95C0(u16 index, u32 value);

void func_0800A1D0(void *context, const u8 *instruction)
{
    func_080C95C0(instruction[1] | (instruction[2] << 8), instruction[3]);
}
