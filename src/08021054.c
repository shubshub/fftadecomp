/* Target bytes (16):
 * 02 49 40 00 40 18 00 88 70 47 00 00 24 12 39 08
 */
#include "ffta.h"

extern const u16 data_08391224[];

u16 func_08021054(u32 index)
{
    return data_08391224[index];
}
