#include "script_record.h"

u16 func_0800A018(void);

u32 func_080CED34(void)
{
    const ScriptRecord *record = &g_table_0854CD54[func_0800A018()];

    return record->unknown_20[1] != 0;
}
