#include "ffta.h"

typedef struct {
    u32 value;
    u32 unknown_04;
    u16 current;
    u16 count;
    u16 history[34];
} State080BC3B0;

typedef void (*BufferInitializer080BC3B0)(void *destination, u32 size);

extern BufferInitializer080BC3B0 const g_callbacks_0836D4B8[];

/* Complete [0x080BC3B0, 0x080BC40C): 92 bytes, 43 instructions. */
void func_080BC3B0(State080BC3B0 *state, u32 value)
{
    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->value = value;
    state->current = 6;
    state->history[state->count++] = state->current;
    state->current = 4;
    state->history[state->count++] = state->current;
    state->current = 2;
    state->history[state->count++] = state->current;
    state->current = 0;
}
