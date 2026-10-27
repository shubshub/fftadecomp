#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u8 *mask;
} MaskState;

extern MaskState data_03002710;

/* 0804E014..0804E030: 28 bytes. */
void func_0804E014(u8 enabled)
{
    *data_03002710.mask = enabled == 0 ? 7 : 0;
}
