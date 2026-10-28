#include "ffta.h"

typedef struct TransferState0801DC24 {
    u8 unknown_00[0x10];
    u8 enabled;
    u8 unknown_11;
    u16 selector;
} TransferState0801DC24;

extern TransferState0801DC24 data_02007F10;
extern u16 data_03003860;
extern u16 func_0801D980(u16 index, u8 mode);

/* Complete [0x0801DC24, 0x0801DC5C): 56 bytes, 22 instructions. */
void func_0801DC24(u16 index)
{
    TransferState0801DC24 *state = &data_02007F10;

    if (state->selector != 0xFF) {
        if (state->enabled != 0)
            data_03003860 = func_0801D980(index, 1);
        else
            func_0801D980(index, 0);
    }
}
