#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[0];
} Struct08064278;

void func_08064278(void)
{
    Struct08064278 *state = *(Struct08064278 **)0x0200F450;

    state->current = 0x30;
    state->entries[state->count++] = 0x30;
    state->current = 0x39;
    state->entries[state->count++] = 0x39;
    state->current = 0x3B;
    state->entries[state->count++] = 0x3B;
    state->current = 0x34;
    state->entries[state->count++] = 0x34;
    state->current = 0x35;
}
