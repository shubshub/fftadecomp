#include "control_flags.h"

typedef struct {
    u8 flags;
    u8 unknown_01[7];
    s16 cursor_y;
    u8 unknown_0a[2];
    u16 scroll_y;
    u16 target_y;
    s8 step;
    u8 frames;
    u8 unknown_12[0x7b];
    u8 compact;
} ScrollPanel;

typedef struct {
    u32 unknown_00;
    ScrollPanel *panel;
} MenuState;

extern MenuState *g_state_03002810;

/* Complete [0x08038B58, 0x08038CDC), 388 bytes and 185 instructions. */
void func_08038B58(void)
{
    s32 position = g_state_03002810->panel->cursor_y - g_state_03002810->panel->scroll_y;
    s32 upper, lower;
    s32 distance;

    if (g_state_03002810->panel->compact) {
        upper = 38;
        lower = 108;
    } else if (!(g_state_03002810->panel->flags & 2)) {
        upper = 38;
        lower = 124;
    } else {
        upper = 62;
        lower = 100;
    }

    /* At 08038BEA and 08038C38 the divisor is the stored byte countdown.
     * C division requires it to be nonzero. If distance / 4 wraps to zero
     * in that byte, the native division helper returns zero. */
    if (position < upper) {
        distance = upper - position;
        g_state_03002810->panel->target_y = g_state_03002810->panel->scroll_y - distance;
        if (distance <= 3) {
            g_state_03002810->panel->frames = distance;
            g_state_03002810->panel->step = -1;
        } else if (distance <= 11) {
            g_state_03002810->panel->frames = distance / 2;
            g_state_03002810->panel->step = -(distance / g_state_03002810->panel->frames);
        } else {
            g_state_03002810->panel->frames = distance / 4;
            g_state_03002810->panel->step = -(distance / g_state_03002810->panel->frames);
        }
    } else if (position > lower) {
        distance = position - lower;
        g_state_03002810->panel->target_y = g_state_03002810->panel->scroll_y + distance;
        if (distance <= 3) {
            g_state_03002810->panel->frames = distance;
            g_state_03002810->panel->step = 1;
        } else if (distance <= 11) {
            g_state_03002810->panel->frames = distance / 2;
            g_state_03002810->panel->step = distance / g_state_03002810->panel->frames;
        } else {
            g_state_03002810->panel->frames = distance / 4;
            g_state_03002810->panel->step = distance / g_state_03002810->panel->frames;
        }
    }

    if (g_state_03002810->panel->frames) {
        g_state_03002810->panel->frames--;
        if (g_state_03002810->panel->frames) {
            g_state_03002810->panel->scroll_y += g_state_03002810->panel->step;
            if (g_state_03002810->panel->step > 0) {
                if (g_state_03002810->panel->scroll_y > 330 - lower)
                    g_state_03002810->panel->scroll_y = 330 - lower;
            } else if (g_state_03002810->panel->scroll_y > 0xF000) {
                ScrollPanel *panel = g_state_03002810->panel;

                panel->scroll_y = 0;
                panel->frames = 0;
            }
        } else {
            g_state_03002810->panel->scroll_y = g_state_03002810->panel->target_y;
        }
    }

    if (g_state_03002810->panel->scroll_y > 0xF000) {
        g_state_03002810->panel->scroll_y = 0;
        g_state_03002810->panel->frames = 0;
    }
    if (g_state_03002810->panel->scroll_y > 192) {
        g_state_03002810->panel->scroll_y = 192;
        g_state_03002810->panel->frames = 0;
    }
    g_control_flags_03000940.bg0vofs = g_state_03002810->panel->scroll_y;
    g_control_flags_03000940.bg1vofs = g_state_03002810->panel->scroll_y;
}
