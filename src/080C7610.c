#include "ffta.h"

typedef struct {
    u32 value;
    u8 unknown_04[0x60];
    u16 phase;
    u8 unknown_66[0x46];
} State080C7610;

typedef void (*BufferInitializer080C7610)(void *destination, u32 size);

extern BufferInitializer080C7610 const g_callbacks_0836D4B8[];
extern State080C7610 data_020158B0;

/* Complete [0x080C7610, 0x080C7638): 40 bytes, 15 instructions. */
void func_080C7610(u32 value)
{
    BufferInitializer080C7610 const *callbacks = g_callbacks_0836D4B8;
    State080C7610 *state = &data_020158B0;

    callbacks[0](state, sizeof(*state));
    state->value = value;
    state->phase = 2;
}
