#include "ffta.h"

/* Complete [0x080895A0, 0x080895D0): 48 bytes, 15 instructions. */
typedef struct DisplayControlState {
    u16 flags;
    u16 background0;
    u16 background1;
    u16 background2;
    u16 background3;
} DisplayControlState;

extern DisplayControlState g_control_flags_03000940;

void func_080895A0(void)
{
    DisplayControlState *state = &g_control_flags_03000940;
    state->background0 = 0xAE0B;
    state->background1 = 0xAC0A;
    state->background2 = 0x2B02;
    state->background3 = 0x2A00;
}
