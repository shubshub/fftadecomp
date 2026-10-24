/* Target bytes: 00b525f7e7fe002200040349884200d10122101c02bc084700000101 */
#include "ffta.h"

extern u16 func_08005BAC(const void *object);

u8 func_080DFDD8(const void *object)
{
    return func_08005BAC(object) == 0x0101;
}
