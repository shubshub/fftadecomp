#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_0048[5];
    u8 mode;
    u8 unknown_004E[3];
    u8 flags;
} CommandState;

typedef struct {
    u8 unknown_0000[0xC];
    u16 command;
} CommandRecord;

extern CommandState *data_0200F450;
extern CommandRecord g_state_020020D0;

/* Complete [0x08063804, 0x08063868): 100 bytes, 46 reachable instructions. */
void func_08063804(void)
{
    CommandState *state;

    g_state_020020D0.command = 0x10;
    data_0200F450->mode = 0x0B;
    data_0200F450->flags = 0x90;

    state = data_0200F450;
    state->entries[state->count++] = state->current;
    state->current = 0x1E;
    state->entries[state->count++] = state->current;
    state->current = 0x37;
    state->entries[state->count++] = state->current;
    state->current = 0x31;
}
