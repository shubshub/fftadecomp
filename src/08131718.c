#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA];
    u8 bound;
} Config08131718;

typedef struct {
    u32 unknown_00;
    Config08131718 *config;
    u8 unknown_08[0x1E];
    u16 flags;
} State08131718;

extern u32 func_08002804(void);
extern s32 func_08142950(s32 value, s32 divisor);

/* Target 0x08131718..0x08131750: 56 bytes. */
s32 func_08131718(State08131718 *state)
{
    if (state->flags & 0x10)
        return state->config->bound;
    else {
        s32 result;
        if (state->config->bound != 0)
            result = func_08142950((s16)func_08002804(), state->config->bound) + 1;
        else
            result = 0;
        return result;
    }
}
