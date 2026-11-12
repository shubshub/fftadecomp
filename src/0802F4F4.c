#include "control_flags.h"

typedef struct {
    u8 unknown_00[0x2A0];
    void *allocation;
} State0802F4F4;

extern State0802F4F4 *data_0200F444;
extern void func_08022854(void *);

/* Complete [0x0802F4F4, 0x0802F560): 108 bytes including three literal words. */
void func_0802F4F4(void)
{
    if (data_0200F444) {
        func_08022854(data_0200F444->allocation);
        data_0200F444 = 0;
        g_control_flags_03000940.winout_lo = 0;
        g_control_flags_03000940.winin_lo = 0;
        g_control_flags_03000940.win0h_hi = (g_control_flags_03000940.win0v_hi = 0);
        g_control_flags_03000940.win0h_lo = (g_control_flags_03000940.win0v_lo = 0);
        g_control_flags_03000940.display &= 0xDFFF;
    }
}
