#include "ffta.h"

typedef struct {
    u8 unknown_00[0xB4];
    u8 active;
} ScriptBattleState;

extern ScriptBattleState g_state_020020D0;
extern u8 g_state_02000080[];

void func_0802D934(void);
void func_0802D824(void);
void func_080D2F2C(void);
void func_0809A950(void *units, s32 count);

u32 func_08123860(void *context, const u8 *script)
{
    ScriptBattleState *state = &g_state_020020D0;

    state->active = 0;
    func_0802D934();
    func_0802D824();
    func_080D2F2C();
    func_0809A950(g_state_02000080, 24);
    return 0x110;
}
