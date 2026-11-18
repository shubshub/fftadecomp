#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1E];
    u16 value;
} Unit081317BC;

typedef struct {
    Unit081317BC *source;
    Unit081317BC *target;
} ActionState081317BC;

/* Evaluator slot 22, [0x081317BC, 0x081317C2). */
s32 func_081317BC(ActionState081317BC *state)
{
    return state->target->value;
}
