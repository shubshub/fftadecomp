#include "selection_state.h"

u16 func_0800A024(void)
{
    u16 index = g_state_020020D0.override_index;

    if (index == 0)
        index = g_state_020020D0.index;
    return index;
}
