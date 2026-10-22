#include "ffta.h"

typedef struct {
    u8 unknown_00[0xAE];
    u8 enabled;
    u8 unknown_AF;
    u16 setting;
} ControlPrefix;

/* Target: 0x08008938, 28 bytes including both literal words. */
void func_08008938(void)
{
    ControlPrefix *control = (ControlPrefix *)0x020020D0;

    control->enabled = 0;
    control->setting = 0;
    *(u16 **)0x02009188 = 0;
}
