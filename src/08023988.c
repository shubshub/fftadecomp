#include "ffta.h"

/* 0x08023988..0x08023A40: 184 bytes. */
typedef struct {
    u8 state;
    u8 active;
    u8 phase;
    u8 unknown_03[3];
    u8 mode;
    u8 unknown_07[6];
    u8 timer;
} MenuState;

typedef struct {
    u8 unknown_00[0x40];
    const void *resource;
} ResourceObject;

extern MenuState g_state_0200F390;
extern u32 data_030027F4;
extern const void *data_030027D4;
extern void func_0802D72C(u32 value);
extern u32 func_0802B880(void);
extern void func_08022CD4(u32 first, u32 second);
extern u32 func_080294FC(void);
extern void *func_08096D7C(void);
extern ResourceObject *func_08099560(void *context, u32 index);

u32 func_08023988(void)
{
    switch (g_state_0200F390.mode) {
    case 0:
        func_0802D72C(1);
        if ((func_0802B880() & 3) == 3)
            g_state_0200F390.mode = 1;
        break;
    case 1:
        {
            ResourceObject *object;

            func_08022CD4(8, 0x10);
            g_state_0200F390.state = 0x13;
            data_030027F4 = func_080294FC();
            object = func_08099560(func_08096D7C(), data_030027F4);
            if (object != 0)
                data_030027D4 = object->resource;
            else
                data_030027D4 = 0;
            g_state_0200F390.mode = 2;
        }
        break;
    case 2:
        if (g_state_0200F390.state == 0) {
            g_state_0200F390.timer = 4;
            g_state_0200F390.mode = 3;
        }
        break;
    case 3:
        if (g_state_0200F390.timer != 0) {
            g_state_0200F390.timer--;
            if (g_state_0200F390.timer != 0)
                break;
        }
        g_state_0200F390.phase = 0x80;
        g_state_0200F390.active = 0;
        return 1;
    }
    return 0x12;
}
