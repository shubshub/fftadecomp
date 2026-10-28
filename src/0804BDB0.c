#include "ffta.h"

/* Complete target: 0x0804BDB0..0x0804BDC4, 20 bytes. */
u8 func_0804BDB0(u8 first, u8 second)
{
    u8 result = 0;

    if (first > second)
        result = 1;
    return result;
}
