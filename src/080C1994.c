#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54E0];
    u32 field_54E0;
} State080C1994;

extern State080C1994 data_020101F8;

/* 0x080C1994..0x080C19A8:
 * 02 48 03 49 40 18 00 68 70 47 00 00 F8 01 01 02 E0 54 00 00. */
u32 func_080C1994(void)
{
    return data_020101F8.field_54E0;
}
