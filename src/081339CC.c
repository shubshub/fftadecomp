#include "ffta.h"

/* 0x081339CC..0x081339F0: 36 bytes, 14 instructions. */
typedef struct {
    u8 flags[12];
} BitRecord;

extern BitRecord data_08527D5C[];
extern u8 func_08131DA4(u8 *flags, s32 index, u8 second);

u8 func_081339CC(u32 record_index, s32 bit_index, u8 second)
{
    return func_08131DA4(data_08527D5C[record_index].flags,
                         bit_index, second);
}
