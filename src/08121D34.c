#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u32 field_10;
} State08121D34;

extern State08121D34 *data_020159CC;

/* 0x08121D34..0x08121D40: 01 48 00 68 00 69 70 47 CC 59 01 02. */
u32 func_08121D34(void)
{
    return data_020159CC->field_10;
}
