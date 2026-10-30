#include "ffta.h"

extern const u8 *const g_table_08526680[];

/* 0x080CB524..0x080CB53C:
 * 00 04 04 49 80 0B F6 22 52 00 80 18 40 18 00 68
 * 70 47 00 00 80 66 52 08. */
const u8 *func_080CB524(u16 index)
{
    return g_table_08526680[index + 123];
}
