#include "ffta.h"

typedef struct {
    const void *first;
    const void *second;
    u8 unknown_08[0x1E];
    u16 flags;
} Pair0813158C;

extern u32 func_08002804(void);
extern s32 func_080C7EA4(const void *object, u32 selector);

/* Complete [0x0813158C, 0x081315D2), 70 bytes:
 * 30b5051ce98c10200840002814d1d1f633f900040014074911f0d4f900040414803428
 * 68142196f777fc6043040a201c06e00000010100002868142196f76cfc30bc02bc0847
 */
s32 func_0813158C(const Pair0813158C *pair)
{
    u32 factor;

    if (pair->flags & 0x10)
        return func_080C7EA4(pair->first, 0x14);
    /* One register carries factor throughout: the remainder is narrowed
     * straight into r4 (0x081315AA), 128 is added in place (0x081315AC)
     * and the product is written back to r4 before the return copy
     * (0x081315B8-0x081315BA). */
    factor = (s16)func_08002804() % 257;
    factor += 128;
    factor = (func_080C7EA4(pair->first, 0x14) * factor) >> 8;
    return factor;
}
