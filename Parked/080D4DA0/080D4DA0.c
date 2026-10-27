#include "ffta.h"

/* 0x080D4DA0..0x080D4DEC: 76 bytes, including the literal pool. */
typedef struct {
    u8 unknown_00[0x46];
    u8 modes;
} ControlModes;

extern ControlModes g_control_flags_03000940;

void func_080D4DA0(u8 low, u8 high)
{
    if (low != 0xFF) {
        g_control_flags_03000940.modes &= 0xF0;
        g_control_flags_03000940.modes |= low;
    }
    if (high != 0xFF) {
        g_control_flags_03000940.modes &= 0x0F;
        g_control_flags_03000940.modes |= high << 4;
    }
}
