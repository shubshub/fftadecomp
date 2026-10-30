#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    const u8 *values;
} State08131024;

extern State08131024 data_0200F3F0;

/* 0x08131024..0x08131030: 12 complete bytes.
 * Target: 0148006b00787047f0f30002.
 */
u8 func_08131024(void)
{
    return data_0200F3F0.values[0];
}
