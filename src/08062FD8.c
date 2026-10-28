#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[8];
    u8 mode;
    u8 timer;
    u8 unknown_52[2];
    u32 flags;
    s32 saved_result;
    s32 result;
    u32 unknown_60;
    u16 field_64;
    u16 field_66;
} CommandState;

extern CommandState *data_0200F450;

/* Complete target: [0x08062FD8, 0x08063060), 136 bytes, 61 instructions. */
void func_08062FD8(void)
{
    CommandState *head = data_0200F450;
    CommandState *state;

    head->saved_result = 0;
    head->timer = 0x10;
    state = data_0200F450;
    state->field_64 = 0x9003;
    state->field_66 = 0x1236;
    state->current = 1;
    state->entries[state->count++] = state->current;
    state->current = 0x12;
    state->entries[state->count++] = state->current;
    state->current = 0x2E;
    state->entries[state->count++] = state->current;
    state->current = 0x28;
    state->entries[state->count++] = state->current;
    state->current = 0x39;
}
