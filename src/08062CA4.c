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
} CommandState08062CA4;

typedef struct {
    u8 unknown_00[0x1F6B];
    u8 setup_value;
    u8 unknown_1f6c[0x3C28 - 0x1F6C];
    u16 index;
} GlobalState08062CA4;

extern GlobalState08062CA4 g_state_02000000;
extern CommandState08062CA4 *data_0200F450;
extern void func_0802DA00(u8 value);

/* Complete [0x08062CA4, 0x08062D48): 164 bytes, 68 instructions. */
void func_08062CA4(void)
{
    CommandState08062CA4 *state;

    g_state_02000000.index = 0;
    func_0802DA00(g_state_02000000.setup_value);
    data_0200F450->previous = 1;
    data_0200F450->timer = 0x10;

    state = data_0200F450;
    state->field_64 = 0x9003;
    state->field_66 = 0x1236;
    state->current = 1;
    state->entries[state->count++] = state->current;
    state->current = 0x37;
    state->entries[state->count++] = state->current;
    state->current = 0x2E;
    state->entries[state->count++] = state->current;
    state->current = 0x28;
    state->entries[state->count++] = state->current;
    state->current = 0x39;
}
