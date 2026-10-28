#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 selector;
    s8 selection;
    u8 unknown_06[0x4E];
} State08096FD8;

typedef void (*BufferInitializer08096FD8)(void *destination, u32 size);

extern BufferInitializer08096FD8 const g_callbacks_0836D4B8[];
extern State08096FD8 data_0200F6A0;

/* Complete [0x08096FD8, 0x08097000): 40 bytes, 15 instructions. */
void func_08096FD8(void)
{
    BufferInitializer08096FD8 const *callbacks = g_callbacks_0836D4B8;
    State08096FD8 *state = &data_0200F6A0;

    callbacks[0](state, sizeof(*state));
    state->selector = 0xFF;
    state->selection = -1;
}
