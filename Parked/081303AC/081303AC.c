#include "ffta.h"

extern u8 func_080CDA7C(const void *object);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u32 func_08002804(void);

/* 0x081303AC..0x081303FA: 78 bytes, 35 instructions. */
s16 func_081303AC(const void *object)
{
    u16 value;
    s16 result;
    s16 random;

    func_080CDA7C(object);
    value = func_080C7EA4(object, 0x14);
    result = (s16)value / 8;
    random = func_08002804();
    result = result - 5 + random % 11;
    if (result <= 0)
        result = 1;
    return result;
}
