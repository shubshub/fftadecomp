#include "ffta.h"

extern const u32 g_table_085680DC[];

/* Complete [0x0813B0A8, 0x0813B0D4), 44 bytes.
 * 10b5031c0021b524a400034a1068984204d1081c07e00000dc80560804320131
 * a142f3d9012010bc02bc0847
 */
u32 func_0813B0A8(u32 key)
{
    u32 index;

    for (index = 0; index < 725; index++) {
        if (g_table_085680DC[index] == key)
            return index;
    }
    return 1;
}
