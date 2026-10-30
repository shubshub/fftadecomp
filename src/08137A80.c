#include "ffta.h"

/* Complete [0x08137A80, 0x08137A9C): 28 bytes, 10 reachable Thumb instructions.
 * 021c1168034848430349401810604000400c70476d4ec64139300000
 */
u16 func_08137A80(void *state)
{
    u32 *value = state;

    *value = *value * 0x41C64E6D + 0x3039;
    return (*value >> 16) & 0x7FFF;
}
