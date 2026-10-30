#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[6];
    u16 mode;
    u8 unknown_50[4];
    u32 flags;
} CommandState08063314;

typedef struct {
    u32 unknown_00;
    u32 selection;
    u32 amount;
} CommandRecord08063314;

extern CommandState08063314 *data_0200F450;
extern CommandRecord08063314 g_state_020020D0;
extern s16 func_08065050(const void *context);
extern u32 func_08065060(void *context);
extern void func_08066028(void *context);

/* Complete [0x08063314, 0x080633F8): 228 bytes, 104 instructions. */
void func_08063314(void)
{
    s16 result = func_08065050(data_0200F450->context);

    if (result == 0)
        return;
    if (result == -1) {
        func_08066028(data_0200F450->context);
        {
            CommandState08063314 *state = data_0200F450;
            state->flags |= 2;
            state->flags |= 4;
            state->mode = 0xB7;
            state->current = 0x13;
            state->entries[state->count++] = 0x13;
            state->current = 0x34;
            state->entries[state->count++] = 0x34;
            state->current = 0x33;
            state->entries[state->count++] = 0x33;
            state->current = 0x32;
        }
    } else {
        g_state_020020D0.selection = func_08065060(data_0200F450->context);
        g_state_020020D0.amount = 5000;
        func_08066028(data_0200F450->context);
        {
            CommandState08063314 *state = data_0200F450;
            state->flags |= 2;
            state->flags |= 1;
            state->flags &= ~4;
            state->mode = 0xB9;
            state->current = 0x19;
            state->entries[state->count++] = 0x19;
            state->current = 0x33;
            state->entries[state->count++] = 0x33;
            state->current = 0x42;
            state->entries[state->count++] = 0x42;
            state->current = 0x32;
        }
    }
}
