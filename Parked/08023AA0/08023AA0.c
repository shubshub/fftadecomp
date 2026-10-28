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
extern void func_0802F400(u32 size);
extern s16 func_0802F560(void);

/* 08023AA0..08023AF4: 84 bytes, 35 instructions. */
u32 func_08023AA0(void)
{
    switch (g_state_0200F390.mode) {
    case 0:
        func_0802F400(0x1c00);
        g_state_0200F390.mode = 1;
        break;
    case 1:
        {
            u16 result;

            if ((result = func_0802F560()) != 0) {
                if ((s16)result < 0)
                    g_state_0200F390.phase = 0x80;
                else
                    g_state_0200F390.phase = 0;
                g_state_0200F390.active = 0;
                return 1;
            }
        }
        break;
    }
    return 0x14;
}
