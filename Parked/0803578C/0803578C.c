#include "ffta.h"

/* Complete target: [0x0803578C, 0x08035844), 184 bytes. */
typedef struct {
    u8 enabled : 1;
    u8 unknown_01 : 4;
    u8 flag_20 : 1;
    u8 flag_40 : 1;
    u8 unknown_07 : 1;
} MenuPanel;

typedef struct {
    u32 unknown_00;
    MenuPanel *panel;
    u8 unknown_08[0xF24 - 8];
    u32 enabled;
    u8 mode_9A;
    u8 unknown_F29[3];
    u8 mode_E6;
    u8 unknown_F2D[3];
    u32 flag_20;
    u32 flag_40;
} MenuState;

typedef struct __attribute__((packed)) {
    u8 mode : 3;
    u8 unknown_03 : 5;
} DisplayFlags;

typedef struct {
    u8 unknown_00[0x9A];
    DisplayFlags flags_9A;
    u8 unknown_9B[0xE6 - 0x9B];
    DisplayFlags flags_E6;
} DisplayState;

extern MenuState *g_state_03002810;
extern DisplayState data_030009E0;

void func_0803578C(void)
{
    data_030009E0.flags_9A.mode = g_state_03002810->mode_9A;
    data_030009E0.flags_E6.mode = g_state_03002810->mode_E6;
    g_state_03002810->panel->flag_20 = g_state_03002810->flag_20;
    g_state_03002810->panel->flag_40 = g_state_03002810->flag_40;
    g_state_03002810->panel->enabled = g_state_03002810->enabled;
}
