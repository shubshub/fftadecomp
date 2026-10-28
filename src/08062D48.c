#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[6];
    u16 field_4e;
    u8 mode;
    u8 unknown_51[0xb];
    s32 result;
} State08062D48;

extern State08062D48 *data_0200F450;

/* Complete [0x08062D48, 0x08062DD6): 142 bytes, 68 instructions. */
void func_08062D48(void)
{
    if (data_0200F450->result == -1) {
        State08062D48 *state;

        data_0200F450->field_4e = 0xad;
        data_0200F450->mode = 3;
        state = data_0200F450;
        state->current = 0x2f;
        state->entries[state->count++] = 0x2f;
        state->current = 0x38;
    } else {
        State08062D48 *state;

        data_0200F450->field_4e = 0xaf;
        data_0200F450->mode = 7;
        state = data_0200F450;
        state->current = 0x0f;
        state->entries[state->count++] = 0x0f;
        state->current = 0x34;
        state->entries[state->count++] = 0x34;
        state->current = 0x35;
        state->entries[state->count++] = 0x35;
        state->current = 0x38;
    }
}
