#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA0];
    u16 index;
} SelectionState;

extern SelectionState g_state_020020D0;

u16 func_0800A018(void)
{
    return g_state_020020D0.index;
}
