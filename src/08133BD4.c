#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    const u8 *values;
} State08133BD4;

extern State08133BD4 data_0200F3F0;

/* 0x08133BD4..0x08133BE0: 12 complete bytes.
 * Target: 0148006b40787047f0f30002.
 */
u8 func_08133BD4(void)
{
    return data_0200F3F0.values[1];
}
