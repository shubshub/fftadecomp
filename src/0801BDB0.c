#include "ffta.h"

typedef struct {
    u8 unknown_00[0x34];
    u8 value;
} State0801BDB0;

extern State0801BDB0 g_state_02007F40;

/* 0x0801BDB0 - 12 bytes */
u8 func_0801BDB0(void)
{
    return g_state_02007F40.value;
}
