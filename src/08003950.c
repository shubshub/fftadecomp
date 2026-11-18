#include "ffta.h"

extern u16 data_030034D4;

/* 0x08003950..0x0800395C: 12 bytes, including the IWRAM address. */
u16 func_08003950(void)
{
    return data_030034D4;
}
