#include "ffta.h"

typedef struct MenuState {
    u8 state;
    u8 active;
    u8 phase;
    u8 sound;
    u8 unknown_04[2];
    u8 mode;
} MenuState;

extern MenuState g_state_0200F390;
extern void func_0802542C(u8 sound);
extern s32 func_08025464(void);

/* 08023A40..08023AA0: 96 bytes, 44 instructions.
 * 10b5044ca07901280fd0012804dc002805d021e090f30002022817d01ce0e07801f0e4fc
 * 0120a07116e001f0fbfc0004010c002810d00804002804da8020a0700220a07108e00020
 * a07002e0a078002802d16070012000e0132010bc02bc0847
 */
u32 func_08023A40(void)
{
    s16 result;

    switch (g_state_0200F390.mode) {
    case 0:
        func_0802542C(g_state_0200F390.sound);
        g_state_0200F390.mode = 1;
        break;
    case 1:
        if ((result = func_08025464()) != 0) {
            if (result < 0) {
                g_state_0200F390.phase = 0x80;
                g_state_0200F390.mode = 2;
            } else {
                g_state_0200F390.phase = 0;
                g_state_0200F390.active = 0;
                return 1;
            }
        }
        break;
    case 2:
        if (g_state_0200F390.phase == 0) {
            g_state_0200F390.active = 0;
            return 1;
        }
        break;
    }
    return 0x13;
}
