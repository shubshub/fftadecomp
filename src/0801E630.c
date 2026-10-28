#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 value;
} State_02007F40;

extern State_02007F40 g_state_02007F40;

/* 0x0801E630: 12 bytes, including the referenced state literal. */
u8 func_0801E630(void)
{
    return g_state_02007F40.value;
}
