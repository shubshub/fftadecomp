#include "ffta.h"

extern u8 g_state_02007F40[];

/* 0x0801E648..0x0801E658: 16 complete bytes, including the mapped-data literal. */
u8 func_0801E648(void)
{
    return (g_state_02007F40[0] >> 7) ^ 1;
}
