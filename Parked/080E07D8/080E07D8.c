#include "ffta.h"

/* Target 0x080E07D8..0x080E07EC (20 bytes):
 * 00 b5 25 f7 e9 f9 00 28 01 d1 00 20 00 e0 01 20 02 bc 08 47
 */
extern u32 func_08005BB0(const void *object);

u32 func_080E07D8(const void *object)
{
    return func_08005BB0(object) != 0;
}
