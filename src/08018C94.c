#include "ffta.h"

/* 08018C94..08018CB6: 34 bytes. */
u16 func_08018C94(u8 *destination, u8 value)
{
    destination[0] = 0x40;
    destination[1] = 0x6C;
    if (value == 3)
        destination[2] = 3;
    else
        destination[2] = 0;
    return 3;
}
