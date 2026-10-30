#include "ffta.h"

typedef struct {
    u8 unknown_00[12];
    u8 *values;
} GlobalState;

extern GlobalState data_03002710;

/* 0x0804ED60..0x0804ED6C: 12 complete bytes, including the mapped-data literal. */
u8 func_0804ED60(void)
{
    return data_03002710.values[3];
}
