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
extern s32 func_08035A20(u8 index);
extern s32 func_08035A44(u8 index);

/* 080362A4..080362DC: 56 bytes. */
void func_080362A4(u8 index)
{
    index--;
    g_state_03002810->window->anchor_x = func_08035A20(index) + 6;
    g_state_03002810->window->anchor_y = func_08035A44(index) + 4;
}
