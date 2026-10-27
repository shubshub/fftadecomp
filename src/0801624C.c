#include "ffta.h"

extern const u8 *const g_table_085516D0[];
extern u16 func_08018C24(u8 *destination, const u8 *source);

u16 func_0801624C(u8 *destination, u8 index)
{
    return func_08018C24(destination, g_table_085516D0[index]);
}
