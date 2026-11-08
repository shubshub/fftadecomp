#include "control_flags.h"

/* 08050D50..08050DA0: 80 bytes. */
extern void func_0804D91C(u32, u32, u32, u32);

void func_08050D50(void)
{
    g_control_flags_03000940.unknown_43 = 0x13;
    g_control_flags_03000940.unknown_3D = 0;
    g_control_flags_03000940.unknown_41 = 8;
    g_control_flags_03000940.unknown_3C = 0xF0;
    g_control_flags_03000940.unknown_40 = 0x18;
    g_control_flags_03000940.display |= 0x4000;
    func_0804D91C(2, 2, 26, 6);
}
