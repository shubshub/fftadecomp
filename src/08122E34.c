#include "ffta.h"

typedef struct CommandState {
    u8 unknown_00[4];
    u16 timer;
} CommandState;

u32 func_08122E34(CommandState *state, const u8 *command)
{
    state->timer = command[1];
    return 0x114;
}
