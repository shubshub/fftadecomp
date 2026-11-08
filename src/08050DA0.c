#include "control_flags.h"

/* 0x08050DA0..0x08050DE8: 72 bytes, including two literal words. */
extern void func_0804D91C(u32, u32, u32, u32);

void func_08050DA0(void)
{
    g_control_flags_03000940.unknown_43 = 0;
    g_control_flags_03000940.unknown_3D = 0;
    g_control_flags_03000940.unknown_41 = 0;
    g_control_flags_03000940.unknown_3C = 0;
    g_control_flags_03000940.unknown_40 = 0;
    g_control_flags_03000940.display &= 0xBFFF;
    func_0804D91C(0, 1, 0x1E, 2);
}
