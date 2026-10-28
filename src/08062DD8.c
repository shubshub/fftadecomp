#include "ffta.h"

typedef struct {
    u8 unknown_00[0x12];
    u8 flag;
} ScriptRecord;

extern ScriptState *data_0200F450;
extern ScriptRecord g_state_020020D0;
extern void func_08066048(u32 value);

/* Complete target: [0x08062DD8, 0x08062E1C), 68 bytes, 28 instructions. */
void func_08062DD8(void)
{
    ScriptState *state;

    func_08066048(data_0200F450->unknown_5c);
    data_0200F450->unknown_4d = 10;
    g_state_020020D0.flag = 0;
    state = data_0200F450;
    state->current = 0x10;
    state->entries[state->count++] = 0x10;
    state->current = 0x31;
}
