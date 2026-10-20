#include "selection_state.h"
#include "script_record.h"

u8 func_080C9540(u16 bitIndex);
u16 func_0800A018(void);

u8 func_080C8530(void)
{
    u8 value;

    if (!func_080C9540(0x253)) {
        const ScriptRecord *record = &g_table_0854CD54[func_0800A018()];

        value = record->values[1];
    } else {
        value = g_state_020020D0.values[1];
    }
    return value;
}
