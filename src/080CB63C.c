#include "ffta.h"

/* Target [0x080CB63C, 0x080CB644): 00880988401a7047. */
s32 func_080CB63C(const void *first, const void *second)
{
    return *(const u16 *)first - *(const u16 *)second;
}
