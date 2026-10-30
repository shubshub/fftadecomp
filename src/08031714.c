#include "ffta.h"

extern u8 data_030027A4;

/* 08031714..08031720: 01 49 FE 20 08 70 70 47 A4 27 00 03. */
void func_08031714(void)
{
    data_030027A4 = 0xFE;
}
