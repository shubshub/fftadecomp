#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[9];
    u8 timer;
    u8 unknown_52[6];
    s32 previous;
    s32 selection;
    s32 saved;
    u16 field_64;
    u16 field_66;
} CommandState080635C0;

extern CommandState080635C0 *data_0200F450;
extern int func_08061DD0(void);

/* Complete [0x080635C0, 0x08063660): 160 bytes, 73 instructions. */
void func_080635C0(void)
{
    CommandState080635C0 *state;

    data_0200F450->saved = data_0200F450->previous;
    data_0200F450->previous = data_0200F450->selection;
    if ((u8)func_08061DD0()) {
        data_0200F450->previous = -1;
        data_0200F450->selection = -1;
    }
    data_0200F450->timer = 0x10;

    state = data_0200F450;
    state->field_64 = 0x9001;
    state->field_66 = 0x1234;
    state->current = 0x1B;
    state->entries[state->count++] = state->current;
    state->current = 0x37;
    state->entries[state->count++] = state->current;
    state->current = 0x2B;
    state->entries[state->count++] = state->current;
    state->current = 0x28;
    state->entries[state->count++] = state->current;
    state->current = 0x39;
}
