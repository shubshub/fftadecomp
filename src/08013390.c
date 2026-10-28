#include "ffta.h"

/* 0x08013390..0x0801339C: 12 bytes. */
extern u32 data_0200918C;

void func_08013390(u32 value)
{
    data_0200918C = value;
}
