#include "ffta.h"

typedef struct {
    u8 unknown_00[12];
    u8 *value;
} GlobalState;

extern GlobalState data_03002710;

/* 0x0804E008..0x0804E014: 12 complete bytes, including the mapped-data literal. */
u8 func_0804E008(void)
{
    return *data_03002710.value;
}
