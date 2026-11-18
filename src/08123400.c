#include "ffta.h"

struct CommandState;

/* Command 60, [0x08123400, 0x08123406). */
u32 func_08123400(struct CommandState *state, const u8 *command)
{
    return 0x110;
}
