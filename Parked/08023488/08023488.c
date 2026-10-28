#include "ffta.h"

typedef struct Display08023488 Display08023488;

typedef struct Menu08023488 {
    u8 unknown_00;
    u8 active;
    u8 phase;
    u8 unknown_03[3];
    u8 mode;
    u8 unknown_07[0x55];
    Display08023488 *display;
} Menu08023488;

typedef struct Mode08023488 {
    u8 unknown_00[0xB3];
    u8 saved_mode;
    u8 unknown_B4[0xE3E];
    unsigned mode : 2;
} Mode08023488;

typedef void (*Copy08023488)(void *destination, const void *source, u32 size);

extern Menu08023488 g_state_0200F390;
extern Mode08023488 g_state_020020D0;
extern Copy08023488 const data_0836D4BC;
extern u8 data_030039F8[];
extern void *func_08022840(u32 size);
extern void func_08022854(void *object);
extern void func_080A9548(void);
extern u32 func_080A9588(void);
extern u8 *func_080CBA84(u32 index);
extern void func_0800975C(Display08023488 *display);
extern u8 func_08008880(void);
extern void func_08023130(void);

/* Complete [0x08023488, 0x08023560): 216 bytes, 82 instructions. */
u32 func_08023488(void)
{
    switch (g_state_0200F390.mode) {
    case 0:
        g_state_0200F390.display = func_08022840(0x1BD0);
        func_080A9548();
        data_0836D4BC(data_030039F8, func_080CBA84(12) + 0x18, 2);
        g_state_0200F390.mode = 1;
        break;
    case 1:
        if ((u8)func_080A9588()) {
            g_state_020020D0.saved_mode = g_state_020020D0.mode;
            func_0800975C(g_state_0200F390.display);
            g_state_0200F390.mode = 2;
        }
        break;
    case 2:
        if (func_08008880()) {
            func_08022854(g_state_0200F390.display);
            g_state_0200F390.display = 0;
            g_state_0200F390.mode = 3;
        }
        break;
    case 3:
        if (g_state_020020D0.saved_mode != g_state_020020D0.mode)
            func_08023130();
        g_state_0200F390.phase = 0x80;
        g_state_0200F390.active = 0;
        return 1;
    }
    return 0x10;
}
