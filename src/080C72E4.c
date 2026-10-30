#include "ffta.h"

typedef struct {
    u8 unknown_00[0xAE];
    u8 value;
} State080C72E4;

extern State080C72E4 data_02015738;

/* 080C72E4..080C72F8: 03 48 AE 30 00 78 40 08 01 21 08 40 70 47 00 00 38 57 01 02. */
u32 func_080C72E4(void)
{
    return (data_02015738.value >> 1) & 1;
}
