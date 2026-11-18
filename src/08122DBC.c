#include "ffta.h"

struct CommandState;

typedef struct {
    u8 unknown_00[0xA4];
    u16 value;
} TextState;

extern TextState g_state_020020D0;

u32 func_08122DBC(struct CommandState *state, const u8 *command)
{
    g_state_020020D0.value = command[1] | (command[2] << 8);
    return 0x110;
}
