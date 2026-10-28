#include "ffta.h"

typedef struct State02007F40 {
    u8 unknown_00[0x0A];
    u16 value;
} State02007F40;

extern State02007F40 g_state_02007F40;

/* 0801E680..0801E68C: 12 bytes, 3 instructions. */
u16 func_0801E680(void)
{
    return g_state_02007F40.value;
}
