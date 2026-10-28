#include "ffta.h"

typedef struct TransferState {
    u8 unknown_00[0x10];
    u8 enabled;
    u8 unknown_11;
    u16 selector;
    u8 unknown_14[2];
    u8 pending;
    u8 unknown_17;
    const u16 *source;
} TransferState;

extern TransferState data_02007F10;
extern u16 data_03003860;
extern u16 data_02008390[161];
extern void func_0814186C(const void *source, void *destination, u32 count);

/* 0801DCB8..0801DD00: 72 bytes, 29 instructions. */
void func_0801DCB8(const u16 *source)
{
    if (data_02007F10.selector == 0xFF)
        return;
    if (data_02007F10.enabled) {
        data_02007F10.pending = 1;
        data_02007F10.source = source;
        data_03003860 = source[0];
    } else {
        func_0814186C(source, data_02008390, 161);
        data_02008390[160] = data_02008390[0];
    }
}
