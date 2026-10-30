/* Target bytes (60):
 * 10 b5 00 04 04 0c 09 04 08 0c 12 04 12 0c 1b 04
 * 19 0c 91 42 0d d2 00 04 00 14 24 04 24 14 00 1b
 * 48 43 11 1c e5 f0 c8 fb 24 18 24 04 24 14 20 1c
 * 01 e0 00 04 00 14 10 bc 02 bc 08 47
 */
#include "ffta.h"

s16 func_0805CF00(u16 start, u16 end, u16 width, u16 position)
{
    if (position < width) {
        s16 value = start;
        s16 limit = end;

        value += (limit - value) * position / width;
        return value;
    } else {
        return (s16)end;
    }
}
