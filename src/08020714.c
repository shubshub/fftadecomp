#include "ffta.h"

typedef struct {
    u8 unknown_00[0x184];
    u8 busy;
} State08020714;

extern State08020714 g_state_02007F40;

/* 0x08020714 - 32 bytes.
 * Target: 00b500210548c222520080180078002800d10121081c02bc08470000407f0002
 */
u8 func_08020714(void)
{
    u8 ready = 0;

    if (g_state_02007F40.busy == 0)
        ready = 1;
    return ready;
}
