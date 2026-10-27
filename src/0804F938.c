#include "ffta.h"

/* 0x0804F938..0x0804F948: 16 bytes. */
extern u8 func_08017180(void *region);

u8 func_0804F938(u8 *state)
{
    return func_08017180(state + 0x1C);
}
