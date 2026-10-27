#include "ffta.h"

extern u8 data_030034D1;
extern u16 data_030034D2;

/* Target: [0x080038E8, 0x08003900), 24 bytes, 8 instructions. */
u16 func_080038E8(u16 value)
{
    data_030034D1 = 0;
    return data_030034D2 = value;
}
