#include "ffta.h"

typedef struct {
    u8 first[0x400];
    u8 second[0x300];
    u32 count;
} State080D2E24;

typedef void (*BufferInitializer080D2E24)(void *destination, u32 size);

extern State080D2E24 data_020021C8;
extern BufferInitializer080D2E24 const g_callbacks_0836D4B8[];

/* Complete [0x080D2E24, 0x080D2E60): 60 bytes, 23 instructions. */
void func_080D2E24(void)
{
    BufferInitializer080D2E24 const *callbacks = g_callbacks_0836D4B8;
    State080D2E24 *state = &data_020021C8;

    callbacks[0](state->first, sizeof(state->first));
    callbacks[0](state->second, sizeof(state->second));
    state->count = 0;
}
