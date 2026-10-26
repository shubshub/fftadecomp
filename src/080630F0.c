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
extern s16 func_08065050(void *context);
extern void func_08066028(void *context);

/* Complete target: [0x080630F0, 0x08063208), 280 bytes, 128 instructions. */
void func_080630F0(void)
{
    s16 result = func_08065050(data_0200F450->context);

    if (result == 0)
        return;
    data_0200F450->result = result;
    data_0200F450->saved_result = result;
    data_0200F450->flags |= 2;
    data_0200F450->timer = 0x10;
    data_0200F450->mode = 3;
    data_0200F450->field_64 = 0x9001;
    data_0200F450->field_66 = 0x1234;
    func_08066028(data_0200F450->context);

    if ((data_0200F450->flags & 4) && result != -1)
        data_0200F450->current = 0x16;
    else
    {
        CommandState *state = data_0200F450;
        state->current = 0x16;
        state->entries[state->count++] = 0x16;
        state->current = 0x15;
        state->entries[state->count++] = 0x15;
        state->current = 0x37;
        state->entries[state->count++] = 0x37;
        state->current = 0x2B;
        state->entries[state->count++] = 0x2B;
        state->current = 0x28;
        state->entries[state->count++] = 0x28;
        state->current = 0x39;
        state->entries[state->count++] = 0x39;
        state->current = 0x3B;
    }
    {
        CommandState *state = data_0200F450;
        state->entries[state->count++] = state->current;
        state->current = 0x32;
        state->entries[state->count++] = 0x32;
        state->current = 0x38;
    }
}
