#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[2];
    u8 phase;
    u8 unknown_04[2];
    u16 position;
    u16 end;
    u8 start;
    u8 width;
    u16 scroll;
    u8 unknown_0e[4];
    u8 mode;
    u8 unknown_13[0x79];
    u8 style;
} Window080365B8;

typedef struct {
    u8 unknown_00[4];
    Window080365B8 *window;
    u8 unknown_08[0x96];
    u16 blocked;
    u8 unknown_a0[0xe9e];
    u8 countdown;
} State080365B8;

typedef struct {
    u8 unknown_00[4];
    u8 *surface;
} Render080365B8;

extern State080365B8 *g_state_03002810;
extern Render080365B8 data_03000E30;

/* Complete [0x080365B8, 0x080366BC): 260 bytes, 111 instructions. */
void func_080365B8(void)
{
    s32 offset;
    u16 width;

    offset = ((g_state_03002810->window->style - 1) & 0x7f) ? -8 : 0;
    g_state_03002810->window->start = g_state_03002810->window->position;
    width = g_state_03002810->window->end - g_state_03002810->window->scroll;
    if (width >= 240)
        width = 240;
    g_state_03002810->window->width = width;

    if (g_state_03002810->blocked == 0 &&
        (g_state_03002810->window->flags & 1) &&
        g_state_03002810->countdown == 0) {
        switch (g_state_03002810->window->mode) {
        case 0:
            func_0804C788(data_03000E30.surface, 0,
                          g_state_03002810->window->start, width);
            break;
        case 1:
            if ((g_state_03002810->window->phase & 15) > 2)
                func_0804C788(data_03000E30.surface, 0,
                              g_state_03002810->window->start + offset,
                              width - offset);
            else
                func_0804C788(data_03000E30.surface, 0,
                              g_state_03002810->window->start, 240);
            break;
        case 2:
            if ((g_state_03002810->window->phase & 7) > 1)
                func_0804C788(data_03000E30.surface, 0,
                              g_state_03002810->window->start + offset,
                              width - offset);
            else
                func_0804C788(data_03000E30.surface, 0,
                              g_state_03002810->window->start, 240);
            break;
        }
    } else {
        func_0804C788(data_03000E30.surface, 0,
                      g_state_03002810->window->start, 240);
    }
    if (g_state_03002810->countdown)
        --g_state_03002810->countdown;
}
