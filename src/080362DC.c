#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    s16 anchor_x;
    u16 anchor_y;
} MenuWindow;

typedef struct {
    void *owner;
    MenuWindow *window;
} MenuContext;

extern MenuContext *g_state_03002810;
extern u8 func_08036330(u8 selector);
extern s32 func_08035A20(u8 index);
extern s32 func_08035A44(u8 index);

/* Complete target: 0x080362DC..0x08036330, 84 bytes. */
u8 func_080362DC(u8 selector)
{
    u8 result;

    if (func_08036330(selector) == 0) {
        result = 0;
    } else {
        g_state_03002810->window->anchor_x =
            func_08035A20(func_08036330(selector) - 1) + 6;
        g_state_03002810->window->anchor_y =
            func_08035A44(func_08036330(selector) - 1) + 4;
        result = 1;
    }
    return result;
}
