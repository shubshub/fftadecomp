#include "ffta.h"

/* 080A7D60 .. 080A7DE0: 128 bytes. */
typedef struct {
    void *context;
    u32 unknown_04;
    u16 current;
    u16 count;
    u16 entries[34];
} State;

extern void (*g_callbacks_0836D4B8[])(void *, u32);

void func_080A7D60(State *state, void *context)
{
    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->context = context;
    state->current = 8;
    state->entries[state->count++] = state->current;
    state->current = 5;
    state->entries[state->count++] = state->current;
    state->current = 3;
    state->entries[state->count++] = state->current;
    state->current = 4;
    state->entries[state->count++] = state->current;
    state->current = 2;
    state->entries[state->count++] = state->current;
    state->current = 0;
}
