#include "ffta.h"

/* Target: 034a918d8023db01181c084390857047407f0002 (20 bytes). */
typedef struct {
    u8 unknown_00[0x2C];
    u16 flags;
} State0801AE34;

extern State0801AE34 g_state_02007F40;

void func_0801AE34(void)
{
    g_state_02007F40.flags |= 0x4000;
}
