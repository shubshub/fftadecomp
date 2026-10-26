#include "ffta.h"

/* Complete [0x08063208, 0x0806327C): 116 bytes, 50 instructions. */
typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[6];
    u16 field_4e;
    u8 unknown_50[4];
    u32 flags;
    s32 selection;
    s32 result;
} CommandState;

typedef struct {
    u8 unknown_0000[0x1F64];
    u32 resource;
} ResourceState;

extern CommandState *data_0200F450;
extern u8 g_state_02000000[];

void func_08063208(void)
{
    CommandState *state = data_0200F450;

    if (state->result == -1 || state->selection == -1) {
        state->field_4e = 0xB8;
        if (state->flags & 0x40) {
            ResourceState *resources = (ResourceState *)g_state_02000000;
            resources->resource += 5000;
            state->flags &= ~0x40;
        }
        data_0200F450->count = 0;
        data_0200F450->current = 0x2F;
    } else {
        state->current = state->entries[--state->count];
    }
}
