/* 0x08007A8C - 54 bytes, complete target [0x08007A8C, 0x08007AC2)
 * Target: 30b5 041c 2404 2414 201c fff7a7fb 051c 5a34 2404 2414
 *         201c fff7a0fb 011c 0904 0914 2d04 2d14 281c 3af100fe
 *         0004 0014 30bc 02bc 0847
 */
#include "ffta.h"

s16 func_080071E8(s16 angle);

/* An inlined copy of func_08007A74 (src/08007A74.c), the cosine: the sine
 * 90 degrees on.  It spans 0x08007A9C-0x08007AAD: angle + 90 and its
 * narrowing (0x08007A9C-0x08007AA0), the call (0x08007AA4) and its s16
 * result narrowed at 0x08007AAA, before the first call's result at
 * 0x08007AAE. */
static inline s16 inlined_08007A74(s16 angle)
{
    return func_080071E8(angle + 90);
}

s16 func_08007A8C(s16 angle)
{
    return func_080071E8(angle) / inlined_08007A74(angle);
}
