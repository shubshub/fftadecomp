#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA6];
    u8 values[2];
} SelectionState;

extern SelectionState g_state_020020D0;

u32 func_081239DC(void *context, const u8 *script)
{
    g_state_020020D0.values[0] = script[1];
    g_state_020020D0.values[1] = script[2];
    return 0x110;
}
