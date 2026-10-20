#include "ffta.h"

typedef struct {
    u8 flags[12];
} BitRecord;

extern BitRecord g_table_0852790C[];

u8 func_08131DA4(u8 *flags, s32 index, u8 second);

u8 func_081339A8(u32 recordIndex, s32 bitIndex, u8 second)
{
    return func_08131DA4(g_table_0852790C[recordIndex].flags, bitIndex, second);
}
