#include "selection_state.h"

void func_08124BB4(u16 selector, u16 value);
u16 func_0800A018(void);
void func_081256D4(u16 value);
u8 func_080C95A8(u16 index);

u32 func_081237D0(void *context, const u8 *script)
{
    SelectionState *state = &g_state_020020D0;

    if (state->override_index) {
        func_08124BB4(state->override_index, state->index);
    } else {
        func_081256D4(func_0800A018());
    }
    return func_080C95A8(13) == 1 ? 0x11A : 0x110;
}
