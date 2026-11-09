#include "control_flags.h"

extern u8 data_0200F3D4[];

extern void func_0800363C(void);
extern void func_08007620(void *state, s16 first, s16 second, s16 third,
                          s16 duration);

/* Complete [0x08022CD4, 0x08022D48): 116 bytes. */
void func_08022CD4(u16 duration, u8 mode)
{
    switch (mode) {
    case 15:
        func_0800363C();
        func_08007620(data_0200F3D4, 16, 0, 0, (s16)duration);
        break;
    case 16:
        g_control_flags_03000940.bldcnt_lo = 255;
        g_control_flags_03000940.bldcnt_hi = 0;
        g_control_flags_03000940.bldy_lo = 0;
        func_08007620(data_0200F3D4, 0, 0, 16, (s16)duration);
        break;
    }
}
