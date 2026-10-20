#include "script_record.h"

extern u8 g_state_02000000[];

u8 func_080C9540(u16 bitIndex);
u16 func_0800A018(void);
u8 func_08036350(u8 selector);
u8 func_08038CDC(u8 index);

u8 func_080CED5C(u8 mode)
{
    if (func_080C9540(0x40))
        return 0;
    if (mode) {
        const ScriptRecord *record = &g_table_0854CD54[func_0800A018()];

        if (record->unknown_20[1] != 0)
            return 0;
        return 1;
    }
    return func_08038CDC(func_08036350(g_state_02000000[0x1F69])) == 8;
}
