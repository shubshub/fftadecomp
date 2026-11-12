#include "control_flags.h"

/* 08087F0C..08087FB8: 172 bytes, including the branch-skipped literal pools. */
extern u8 data_030027A4;
extern u16 data_030027F0;
extern u16 data_04000050;
extern struct {
    u8 unknown_00[8];
    u16 flags;
} data_03000EA0;

void func_08087F0C(void)
{
    if (data_030027A4 == 0xFF) {
        g_control_flags_03000940.bldcnt_lo = 0x44;
        g_control_flags_03000940.bldcnt_hi = 0x11;
        data_04000050 = data_030027F0;
    } else if (data_030027A4 == 0xFD) {
        g_control_flags_03000940.bldcnt_lo = data_030027F0;
        g_control_flags_03000940.bldcnt_hi = data_030027F0 >> 8;
        data_04000050 = data_030027F0;
    } else {
        g_control_flags_03000940.bldcnt_lo = data_030027F0;
        g_control_flags_03000940.bldcnt_hi = data_030027F0 >> 8;
        data_04000050 = data_030027F0;
        data_03000EA0.flags = (data_03000EA0.flags & 0xFF) |
                            ((data_030027A4 << 8) | 0x20);
    }
}
