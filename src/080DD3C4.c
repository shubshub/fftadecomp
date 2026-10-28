#include "ffta.h"

/* 0x080DD3C4..0x080DD3EE: 42 bytes. */
extern u8 func_080DD3F0(void **destination);
extern u8 func_080DD434(void **destination);

u8 func_080DD3C4(void **destination)
{
    u32 count = func_080DD3F0(destination);
    count += func_080DD434(destination + count);
    return count;
}
