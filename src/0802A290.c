#include "ffta.h"

/* 0x0802A290..0x0802A2B6: 38 bytes / 16 instructions. */
extern void func_08017508(void *window, u8 appearance);
extern void func_08017D18(void *control, u8 flags);

void func_0802A290(u8 *state, u8 appearance)
{
    func_08017508(state, appearance);
    func_08017D18(state + 0x4C, 0);
    func_08017D18(state + 0x60, 0);
}
