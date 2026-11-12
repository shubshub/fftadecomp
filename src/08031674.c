#include "control_flags.h"

extern u8 data_030027A4;

/* Complete [0x08031674, 0x08031698): 36 bytes, including two literal words. */
void func_08031674(void)
{
    data_030027A4 = 0xFD;
    g_control_flags_03000940.bldcnt_lo = 0x42;
    g_control_flags_03000940.bldcnt_hi = 1;
}
