#include "ffta.h"

extern const u8 *func_08018518(u8 index);

/* 080185B8..080185C8: 16 bytes, 7 instructions. */
u8 func_080185B8(u8 index)
{
    return *func_08018518(index);
}
