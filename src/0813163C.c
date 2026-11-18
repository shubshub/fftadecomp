#include "ffta.h"

/* Action evaluator slot 12, 0x0813163C..0x08131694.
 * 30b5041c00f02cf9051ce18c10200840002817d1d1f6d8f8000400140b4911f079f9000400148030291c48430512002d00d10d1c0648854200da051c0548854200dd051c281c30bc02bc08470101000019fcffffe7030000
 */
typedef struct {
    void *source;
    void *target;
    u8 unknown_08[4];
    u16 entry;
    u16 first;
    u8 unknown_10[0x16];
    u16 flags;
} Context;

extern s32 func_0813189C(const Context *context);
extern u32 func_08002804(void);

s32 func_0813163C(Context *context)
{
    s32 value = func_0813189C(context);

    if (!(context->flags & 0x10)) {
        s32 factor = (s16)((s16)func_08002804() % 257) + 128;
        s32 original = value;
        value = (factor * original) >> 8;
        if (value == 0)
            value = original;
        if (value < -999)
            value = -999;
        if (value > 999)
            value = 999;
    }
    return value;
}
