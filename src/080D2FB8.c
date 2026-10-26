#include "ffta.h"

/* 0x080D2FB8..0x080D2FD6: 30 bytes, 12 instructions, including a pool. */
u32 func_080D2FB8(u16 id)
{
    u16 relative = id - 0x150;

    if (relative <= 0x16) {
        return 1;
    }
    return 0;
}
