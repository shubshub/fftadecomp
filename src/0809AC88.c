#include "ffta.h"

/* 0x0809AC88..0x0809ACA2: 26 bytes. */
typedef struct {
    u8 unknown_00[0x74];
    s8 enabled;
} FlagState;

u32 func_0809AC88(FlagState *state, u32 *result)
{
    if (state->enabled == 0)
        return 1;
    *result = 1;
    return 1;
}
