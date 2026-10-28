#include "ffta.h"

/* 0x08050DE8..0x08050E14: 44 bytes / 16 instructions. */
extern void func_08017508(void *window, u8 appearance);
extern void func_08017D18(void *control, u8 flags);
extern u8 func_0804F938(u8 *state);
extern u8 func_080098F4(u8 (*callback)(u8 *state), u8 *state);

void func_08050DE8(u8 *state)
{
    func_08017508(state + 0x1C, state[0x14]);
    func_08017D18(state + 0x68, 0);
    state[9] = func_080098F4(func_0804F938, state);
}
