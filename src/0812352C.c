#include "ffta.h"

/* Complete [0x0812352C, 0x08123564): 56 bytes, 25 instructions plus the
 * 0x115 return literal.  Decodes the inclusive nibble range in script[2]
 * and passes its start and length to func_08127AF8. */

void func_08127AF8(void *owner, u8 first, u8 second, u8 count, u8 third,
                   u8 mode);

u32 func_0812352C(void *context, const u8 *script)
{
    s8 start = script[2] & 0xF;
    s8 end = script[2] >> 4;

    func_08127AF8(context, script[1], start, end - start + 1, script[3], 0);
    return 0x115;
}
