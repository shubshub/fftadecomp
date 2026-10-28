#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1B];
    u8 count;
} MenuState;

extern MenuState *data_0200F44C;
extern u32 func_08060154(u32 index, u8 offset);

/* Complete target: [0x080601B4, 0x080601D0), 28 bytes, 11 instructions. */
u32 func_080601B4(const void *control, u32 index)
{
    return func_08060154(index, data_0200F44C->count - 2);
}
