#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA0];
    u16 index;
    u16 override_index;
} SelectionState;

extern SelectionState g_state_020020D0;

u16 func_0800A024(void)
{
    u16 index = g_state_020020D0.override_index;

    if (index == 0)
        index = g_state_020020D0.index;
    return index;
}
