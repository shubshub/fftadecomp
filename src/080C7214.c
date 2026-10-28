#include "ffta.h"

/* 0x080C7214..0x080C7240: 44 bytes / 16 instructions. */
typedef struct {
    u8 unknown_00[2];
    u8 state;
    u8 unknown_03;
    u16 x;
    u16 y;
    u8 unknown_08[0x88];
} State080C7214;

typedef void (*BufferInitializer080C7214)(void *, u32);

extern State080C7214 data_02015744;
extern BufferInitializer080C7214 const g_callbacks_0836D4B8[];

void func_080C7214(void)
{
    State080C7214 *state = &data_02015744;

    g_callbacks_0836D4B8[0](state, 0x90);
    state->state = 0;
    state->x = 216;
    state->y = 152;
}
