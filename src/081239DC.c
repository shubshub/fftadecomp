#include "selection_state.h"

u32 func_081239DC(void *context, const u8 *script)
{
    g_state_020020D0.values[0] = script[1];
    g_state_020020D0.values[1] = script[2];
    return 0x110;
}
