/* func_08009FF8 - complete [0x08009FF8, 0x0800A018): 32 bytes, 11 instructions.
 *   target  00b5 0648 bff0a0fa 0006 0028 03d0 0348 0021 bff0b3fa 01bc 0047 0000
 *   pool 0x0800A014: 0x0000021F
 *
 * Clears flag 0x21F when it is set; func_08009FD0 sets the same flag.
 */

#include "ffta.h"

u8 func_080C9540(u16 bitIndex);
void func_080C9574(u16 bitIndex, u16 enabled);

/* An inlined copy of func_08009FBC (src/08009FBC.c). */
static inline u8 inlined_08009FBC(void)
{
    return func_080C9540(0x21F);
}

void func_08009FF8(void)
{
    if (inlined_08009FBC())
        func_080C9574(0x21F, 0);
}
