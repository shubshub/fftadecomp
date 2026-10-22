#include "ffta.h"

u8 func_08017180(void *state);

/* Target: 0x08008E78, 28 bytes including the required literal word. */
u16 func_08008E78(u32 context)
{
    u8 **active = (u8 **)0x02009188;

    return func_08017180(*active + 0x2C4);
}
