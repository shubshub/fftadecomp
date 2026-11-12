#include "control_flags.h"

extern u16 data_0200F3D4[];
extern u32 func_08007894(const void *state);
extern void func_080076F4(void *state);

/* Complete [0x08022D48, 0x08022DD0): 136 bytes including literal pools. */
u32 func_08022D48(u8 mode)
{
    switch (mode) {
    case 15:
        if (func_08007894(data_0200F3D4)) {
            g_control_flags_03000940.bldcnt_lo = 0;
            g_control_flags_03000940.bldy_lo = 0;
            return 1;
        }
        func_080076F4(data_0200F3D4);
        g_control_flags_03000940.bldy_lo = data_0200F3D4[0];
        break;
    case 16:
        if (func_08007894(data_0200F3D4)) {
            g_control_flags_03000940.bldy_lo = mode;
            return 1;
        }
        func_080076F4(data_0200F3D4);
        g_control_flags_03000940.bldy_lo = data_0200F3D4[0];
        break;
    }
    return 0;
}
