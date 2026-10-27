#include "ffta.h"

/* 0x0813109C..0x081310B2: 22 bytes. */
typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} FlagState;

int func_0813109C(const FlagState *state)
{
    if ((state->flags & 1) == 0)
        return 0;
    return 100;
}
