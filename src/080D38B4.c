#include "control_flags.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
} DisplayState080D38B4;

extern void *data_020159C0;
extern void *func_08005BFC(void *task);
extern void func_08003620(u8 value);
extern u16 func_080035A8(u8 index);

/* Complete [0x080D38B4, 0x080D3904): 80 bytes, including two literal words. */
void func_080D38B4(void)
{
    DisplayState080D38B4 *state = func_08005BFC(data_020159C0);

    func_08003620(0);
    g_control_flags_03000940.display &= ~func_080035A8(2);
    g_control_flags_03000940.display &= ~func_080035A8(3);
    if ((state->flags & 16) == 0)
        g_control_flags_03000940.bldcnt_lo = 0;
}
