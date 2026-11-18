#include "ffta.h"

typedef struct CommandState {
    s16 position;
} CommandState;

u32 func_08122E7C(CommandState *state, const u8 *command)
{
    u32 displacement = command[1] | (command[2] << 8);

    state->position += displacement;
    return 0x110;
}
