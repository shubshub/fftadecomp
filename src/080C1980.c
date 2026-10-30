#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54E0];
    u32 value;
} State080C1980;

extern State080C1980 data_020101F8;

/* 080C1980..080C1994: 02 49 03 4A 89 18 08 60 70 47 00 00 F8 01 01 02 E0 54 00 00. */
void func_080C1980(u32 value)
{
    data_020101F8.value = value;
}
