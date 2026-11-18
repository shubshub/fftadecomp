#include "ffta.h"

extern u8 g_state_0200F390;

u32 func_08122D64(void *state, const u8 *command)
{
    g_state_0200F390 = 12;
    return 0x112;
}
