#include "control_flags.h"

// Complete target bytes (0x080D4DA0..0x080D4DEC, 76 bytes):
// 10b50006030e09060c0eff2b0bd00e4946310a78f02010400a7808700a78181c10430a78
// 0870ff2c0bd0074946310a780f2010400a78087020010a7810430a78087010bc01bc0047
// 40090003
void func_080D4DA0(u8 low, u8 high)
{
    if (low != 0xFF) {
        g_control_flags_03000940.mosaic_lo &= 0xF0;
        g_control_flags_03000940.mosaic_lo |= low;
    }
    if (high != 0xFF) {
        g_control_flags_03000940.mosaic_lo &= 0x0F;
        g_control_flags_03000940.mosaic_lo |= high << 4;
    }
}
