#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x219E];
    u16 field_219e;
} StateView;

extern u8 g_state_02000000[];

void func_080C95C0(u16 index, u32 value);
void func_08004C40(void);

void func_080642D8(void)
{
    ScriptState *configuration;
    ScriptState *state;

    func_080C95C0(0x0D, 0);
    func_08004C40();
    ((StateView *)g_state_02000000)->field_219e = 0;
    configuration = *(ScriptState **)0x0200F450;
    configuration->field_4e = 0xA6;
    configuration->unknown_4d = 1;
    state = *(ScriptState **)0x0200F450;
    state->current = 2;
    state->entries[state->count++] = 2;
    state->current = 0x31;
    state->entries[state->count++] = 0x31;
    state->current = 0x34;
    state->entries[state->count++] = 0x34;
    state->current = 0x35;
}
