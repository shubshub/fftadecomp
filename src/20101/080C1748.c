#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54CC];
    u8 values[4];
    u8 mode : 4;
    u8 next : 4;
} State080C1748;

void func_080C1748(void)
{
    State080C1748 *state = (State080C1748 *)0x020101F8;

    state->values[state->next++] = 4;
}
