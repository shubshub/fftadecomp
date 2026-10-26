#include "ffta.h"

typedef struct {
    u8 enabled;
    u8 unknown_01[0x1B];
    u16 x;
    u16 y;
} SecondaryLayer;

typedef struct {
    u8 enabled;
    u8 unknown_01[3];
} ScrollAxis;

typedef struct {
    u8 background0;
    u8 background1;
    u8 unknown_02[0x22];
    s16 focusX;
    s16 focusY;
    s16 originX;
    s16 originY;
    u16 flags;
    u8 unknown_2E[0x156];
    SecondaryLayer secondary;
    u8 unknown_1A4[0x74];
    ScrollAxis horizontal;
    ScrollAxis vertical;
    u8 unknown_220[4];
    u16 offsetX;
    u16 offsetY;
} ScrollState;

extern ScrollState g_state_02007F40;
extern void func_08003508(s16 offset, u8 background);
extern void func_08003558(s16 offset, u8 background);

/* Complete target: [0x08019B48, 0x08019C74), 300 bytes, 135 instructions. */
void func_08019B48(void)
{
    s16 x = g_state_02007F40.focusX - g_state_02007F40.originX;
    s16 y = g_state_02007F40.focusY - g_state_02007F40.originY;

    if (g_state_02007F40.flags & 0x400)
    {
        if (g_state_02007F40.horizontal.enabled)
            x += g_state_02007F40.offsetX;
        if (g_state_02007F40.vertical.enabled)
            y += g_state_02007F40.offsetY;
    }
    func_08003508(x, g_state_02007F40.background0);
    func_08003558(y, g_state_02007F40.background0);
    func_08003508(x, g_state_02007F40.background1);
    func_08003558(y, g_state_02007F40.background1);

    if (g_state_02007F40.flags & 0x400)
    {
        SecondaryLayer *secondary = &g_state_02007F40.secondary;

        if (secondary->enabled)
        {
            if (g_state_02007F40.horizontal.enabled)
                x = g_state_02007F40.offsetX + secondary->x;
            if (g_state_02007F40.vertical.enabled)
                y = g_state_02007F40.offsetY + secondary->y;
            func_08003508(x, 2);
            func_08003558(y, 2);
            func_08003508(x, 3);
            func_08003558(y, 3);
        }
    }
    g_state_02007F40.flags &= ~0x200;
}
