#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54CC];
    u8 values[4];
    u8 mode : 4;
    u8 next : 4;
} State080C1700;

void func_080C1700(u8 mode)
{
    State080C1700 *state = (State080C1700 *)0x020101F8;

    state->mode = mode;
    state->values[state->next++] = 0;
}
