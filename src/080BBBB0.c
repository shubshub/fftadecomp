#include "ffta.h"

typedef struct State080BBBB0 {
    void *context;
    u8 unknown_04[4];
    u16 parameter;
    u8 unknown_0A[2];
    u16 current;
    u16 count;
    u16 steps[5];
    u8 unknown_1A[0x3A];
} State080BBBB0;

typedef void (*StateInitializer080BBBB0)(void *destination, u32 size);

extern StateInitializer080BBBB0 const g_callbacks_0836D4B8[];

static inline void queue_state(State080BBBB0 *state, u16 next)
{
    state->current = next;
    state->steps[state->count++] = next;
}

/* Complete [0x080BBBB0, 0x080BBC38): 136 bytes, 64 instructions. */
void func_080BBBB0(State080BBBB0 *state, void *context, u16 parameter)
{
    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->context = context;
    state->parameter = parameter;
    queue_state(state, 8);
    queue_state(state, 6);
    queue_state(state, 4);
    queue_state(state, 2);
    queue_state(state, 3);
    state->current = 0;
}
