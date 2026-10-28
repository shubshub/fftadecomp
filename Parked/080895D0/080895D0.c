#include "ffta.h"

typedef struct {
    u16 display_flags;
    u16 background_control[4];
} DisplayControls080895D0;

extern DisplayControls080895D0 g_control_flags_03000940;

/* Complete target [0x080895D0, 0x08089600): 48 bytes, 14 instructions. */
void func_080895D0(void)
{
    DisplayControls080895D0 *controls = &g_control_flags_03000940;

    controls->background_control[0] = 0xAE0B;
    controls->background_control[1] = 0xAC0A;
    controls->background_control[2] = 0x2B0A;
    controls->background_control[3] = 0x2A08;
}
