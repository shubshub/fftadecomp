#include "selection_state.h"
#include "script_record.h"

u8 func_080C9540(u16 bitIndex);
u16 func_0800A018(void);

u8 func_080C84F4(void)
{
    const u8 *values;

    if (!func_080C9540(0x253)) {
        const ScriptRecord *record = &g_table_0854CD54[func_0800A018()];

        values = record->values;
    } else {
        const SelectionState *state = &g_state_020020D0;

        values = state->values;
    }
    return values[0];
}
