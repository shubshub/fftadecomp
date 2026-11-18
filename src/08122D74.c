#include "control_flags.h"

struct CommandState;

/* Command 14 enables or disables BG0 and BG1 together in the display shadow. */
u32 func_08122D74(struct CommandState *state, const u8 *command)
{
    if (command[1])
        g_control_flags_03000940.display |= 0x300;
    else
        g_control_flags_03000940.display &= ~0x300;
    return 0x110;
}
