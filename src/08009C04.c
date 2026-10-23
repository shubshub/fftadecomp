#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA0];
    u16 field_a0;
    u16 field_a2;
} State08009C04;

/* Target: 0x08009C04..0x08009C18, 20 bytes including alignment and literal. */
void func_08009C04(u16 first, u16 second)
{
    State08009C04 *state = (State08009C04 *)0x020020D0;

    state->field_a0 = first;
    state->field_a2 = second;
}
