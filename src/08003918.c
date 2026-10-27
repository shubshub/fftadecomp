#include "ffta.h"

/* 0x08003918..0x08003934: 28 bytes. */
extern u8 data_030034D1;
extern u16 data_030034D2;

void func_08003918(void)
{
    data_030034D1 = 0;
    data_030034D2 = 0xFFFE;
}
