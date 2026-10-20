#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA0];
    u16 value;
    u16 selector;
} ScriptTransferState;

extern ScriptTransferState g_state_020020D0;

void func_08124BB4(u16 selector, u16 value);
u16 func_0800A018(void);
void func_081256D4(u16 value);
u8 func_080C95A8(u16 index);

u32 func_081237D0(void *context, const u8 *script)
{
    ScriptTransferState *state = &g_state_020020D0;

    if (state->selector) {
        func_08124BB4(state->selector, state->value);
    } else {
        func_081256D4(func_0800A018());
    }
    return func_080C95A8(13) == 1 ? 0x11A : 0x110;
}
