#include "ffta.h"

extern u8 data_030034D1;
extern u16 data_030034D2;

/* 0x080038C8..0x080038E8: 32 complete bytes, including both mapped-data literals. */
void func_080038C8(u16 value)
{
    data_030034D1 = 0;
    data_030034D2 = value | 0x8000;
}
