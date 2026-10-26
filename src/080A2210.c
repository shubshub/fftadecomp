#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 value;
} HalfwordRecord;

extern u8 func_080C8280(const void *object);
extern u8 func_080CD92C(const void *object);
extern u8 func_080CDCBC(const void *object);
extern s32 func_080C7EA4(const void *object, u32 selector);

/* 0x080A2210..0x080A22EE: 222 bytes. */
u32 func_080A2210(HalfwordRecord *object, s16 amount)
{
    u8 before;
    u32 after;
    s16 value;

    if (func_080C8280(object))
        after = 1;
    else if (func_080CD92C(object) ? func_080CDCBC(object) :
             (u32)func_080C7EA4(object, 0x13) <=
                 ((u32)func_080C7EA4(object, 0x14) >> 2))
        after = 2;
    else
        after = 3;

    before = after;

    value = func_080C7EA4(object, 0x13);
    value -= (s16)amount;
    if (value < 0)
        value = 0;
    if ((u32)value > (u32)func_080C7EA4(object, 0x14))
        value = func_080C7EA4(object, 0x14);
    object->value = value;

    if (func_080C8280(object))
        after = 1;
    else if (func_080CD92C(object) ? func_080CDCBC(object) :
             (u32)func_080C7EA4(object, 0x13) <=
                 ((u32)func_080C7EA4(object, 0x14) >> 2))
        after = 2;
    else
        after = 3;
    if (after == before)
        after = 0;
    return after;
}
