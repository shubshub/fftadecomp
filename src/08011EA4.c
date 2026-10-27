#include "ffta.h"

extern u8 *data_0200918C;
extern u8 func_08017180(u8 *region);

/* 08011EA4..08011EBC: 24 bytes. */
u8 func_08011EA4(void)
{
    return func_08017180(data_0200918C + 0x44);
}
