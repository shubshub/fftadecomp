#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[5];
    u8 phase;
    u16 field_4e;
    u8 mode;
    u8 unknown_51[3];
    u32 flags;
    u32 unknown_58;
    s32 result;
    u32 unknown_60;
    u16 field_64;
    u16 field_66;
} State08062834;

typedef struct {
    u8 unknown_00[0x12];
    u8 flag;
} Record08062834;

extern State08062834 *data_0200F450;
extern Record08062834 g_state_020020D0;
extern s16 func_08065050(void *);
extern u32 func_08065060(void *);
extern void func_0806603C(u32);
extern void func_08066028(void *);

/* Complete [0x08062834, 0x0806297C): 328 bytes, 150 instructions. */
void func_08062834(void)
{
    s16 result = func_08065050(data_0200F450->context);

    if (result == 0)
        return;
    if (result == -1) {
        State08062834 *state;

        data_0200F450->result = result;
        data_0200F450->field_4e = 0xad;
        data_0200F450->flags |= 2;
        data_0200F450->mode = 3;
        data_0200F450->field_64 = 0x9001;
        data_0200F450->field_66 = 0x1234;
        func_08066028(data_0200F450->context);

        state = data_0200F450;
        state->current = 0x30;
        state->entries[state->count++] = 0x30;
        state->current = 0x39;
        state->entries[state->count++] = 0x39;
        state->current = 0x3b;
        state->entries[state->count++] = 0x3b;
        state->current = 0x34;
        state->entries[state->count++] = 0x34;
        state->current = 0x33;
        state->entries[state->count++] = 0x33;
        state->current = 0x29;
        state->entries[state->count++] = 0x29;
        state->current = 0x28;
        state->entries[state->count++] = 0x28;
        state->current = 0x39;
        state->entries[state->count++] = 0x39;
        state->current = 0x32;
    } else {
        State08062834 *state;

        func_0806603C(func_08065060(data_0200F450->context));
        data_0200F450->phase = 9;
        g_state_020020D0.flag = 0;
        func_08066028(data_0200F450->context);

        state = data_0200F450;
        state->current = 0x0a;
        state->entries[state->count++] = 0x0a;
        state->current = 0x31;
        state->entries[state->count++] = 0x31;
        state->current = 0x32;
    }
}
