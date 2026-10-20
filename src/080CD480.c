#include "ffta.h"

extern const u8 *const g_table_0851BA84[];

const u8 *func_080CD480(u8 first, u8 second)
{
    return g_table_0851BA84[first] + second * 8;
}
