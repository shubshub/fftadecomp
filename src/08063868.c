#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[12];
    u32 flags;
} CommandState;

extern CommandState *data_0200F450;
extern void func_08066028(void *context);

/* Complete target: [0x08063868, 0x080638C8), 96 bytes, 44 instructions. */
void func_08063868(void)
{
    func_08066028(data_0200F450->context);
    {
        CommandState *state = data_0200F450;
        state->current = 0x30;
        state->entries[state->count++] = 0x30;
        state->current = 0x39;
        state->entries[state->count++] = 0x39;
        state->current = 0x3B;
        state->entries[state->count++] = 0x3B;
        state->current = 0x32;
        state->flags &= ~0x40;
    }
}
