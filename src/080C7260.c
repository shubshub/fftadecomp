#include "ffta.h"

typedef struct State080C7260 {
    u8 unknown_00[0xB0];
    u16 enabled;
    u8 unknown_B2[0x46];
} State080C7260;

typedef void (*BufferInitializer080C7260)(void *destination, u32 size);

extern State080C7260 data_02015738;
extern BufferInitializer080C7260 const g_callbacks_0836D4B8[];

/* Complete [0x080C7260, 0x080C7284): 36 bytes, 13 instructions. */
void func_080C7260(void)
{
    State080C7260 *state = &data_02015738;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->enabled = 1;
}
