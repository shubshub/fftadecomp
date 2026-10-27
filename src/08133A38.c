#include "ffta.h"

/* 0x08133A38..0x08133A58: 32 bytes. */
u8 func_08133A38(const u8 *bits, int index)
{
    int byte_index = index >> 3;
    int bit_index = index & 7;

    if (((bits[byte_index] >> bit_index) & 1) == 0)
        return 0;
    return 1;
}
