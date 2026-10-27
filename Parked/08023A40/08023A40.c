#include "ffta.h"

typedef struct MenuState {
    u8 state;
    u8 active;
    u8 phase;
    u8 sound;
    u16 selection;
    u8 mode;
} MenuState;

extern MenuState g_state_0200F390;
extern void func_0802542C(u8 sound);
extern u32 func_08025464(void);

/* 08023A40..08023AA0: 96 bytes, 44 instructions. */
u32 func_08023A40(void)
{
    switch (g_state_0200F390.mode) {
    case 0:
        func_0802542C(g_state_0200F390.sound);
        g_state_0200F390.mode = 1;
        break;
    case 1:
        {
            s32 result = (u16)func_08025464();

            if (result != 0) {
                if ((s16)result < 0) {
                    g_state_0200F390.phase = 0x80;
                    g_state_0200F390.mode = 2;
                } else {
                    g_state_0200F390.phase = 0;
                    g_state_0200F390.active = 0;
                    return 1;
                }
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
