#include "ffta.h"

/* Complete 0x0812F704..0x0812F770: 108 bytes, 46 instructions. */
extern s32 func_080C7EA4(void *actor, u16 attribute);
extern u8 func_080C95A8(u16 condition);
extern u8 func_080C8240(void *actor);
extern u8 func_080D2BF4(u16 modifier);

s32 func_0812F704(void *actor, u16 alternate)
{
    s32 value;

    if (alternate == 0) {
        value = func_080C7EA4(actor, 24);
        if (!func_080C95A8(13) && !func_080C8240(actor))
            value += value * func_080D2BF4(11) / 100;
    } else {
        value = func_080C7EA4(actor, 26);
        if (!func_080C95A8(13) && !func_080C8240(actor))
            value += value * func_080D2BF4(13) / 100;
    }
    return value;
}
