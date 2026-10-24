#include "ffta.h"

extern u32 func_08005BB0(const void *object);

/* Target 0x080DFEB8..0x080DFECC (20 bytes):
 * 00 b5 25 f7 79 fe 00 28 01 d1 00 20 00 e0 01 20 02 bc 08 47
 */
u32 func_080DFEB8(const void *object)
{
    return func_08005BB0(object) != 0;
}
