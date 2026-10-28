#include "ffta.h"

typedef struct {
    u8 unknown_00[0xAC];
    u8 count;
    u8 unknown_AD[3];
    u16 phase;
    u8 unknown_B2[0x46];
} State080C7284;

typedef void (*BufferInitializer080C7284)(void *destination, u32 size);

extern State080C7284 data_02015738;
extern BufferInitializer080C7284 const g_callbacks_0836D4B8[];

/* Complete [0x080C7284, 0x080C72B0): 44 bytes, 17 instructions. */
void func_080C7284(void)
{
    State080C7284 *state = &data_02015738;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->phase = 1;
    state->count = 7;
}
