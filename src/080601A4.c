#include "ffta.h"

extern u32 func_08060154(u32 index, u8 offset);

/* Complete target: [0x080601A4, 0x080601B2), 14 bytes, 6 instructions.
 * Target bytes: 00b5081c0021fff7d3ff02bc0847
 */
u32 func_080601A4(const void *control, u32 index)
{
    return func_08060154(index, 0);
}
