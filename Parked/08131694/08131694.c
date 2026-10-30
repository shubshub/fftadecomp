#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u16 value;
} Entry08131694;

typedef struct {
    const Entry08131694 *first;
    const Entry08131694 *second;
    u8 unknown_08[0x1E];
    u16 flags;
} Pair08131694;

extern u32 func_08002804(void);

/* Complete target [0x08131694, 0x08131704), 112 bytes:
 * 30b5041ce18c1025281c0840002802d06068408b24e0d1f6abf800040014084911f04cf900040014031c80332068428be18c281c0840002804d0101c10e0000001010000101c584302120748824200da021c0648824200dd021c181c5043001230bc02bc0847000019fcffffe7030000
 */
s32 func_08131694(const Pair08131694 *pair)
{
    s16 remainder;
    s32 factor;
    s32 value;

    if (pair->flags & 0x10)
        return pair->second->value;

    remainder = (s16)func_08002804() % 257;
    factor = remainder + 128;
    value = pair->first->value;
    if (pair->flags & 0x10)
        return value;

    value = (value * factor) >> 8;
    if (value < -999)
        value = -999;
    if (value > 999)
        value = 999;
    return (factor * value) >> 8;
}
