#include "ffta.h"

struct ActionPanel {
    u8 unknown_00[0x8E];
    u8 state : 3;
    u8 unknown_473 : 5;
};

struct MenuState {
    void *actions;
    struct ActionPanel *panel;
};

extern struct MenuState *g_state_03002810;

/* 0x0804413C..0x08044158, 24 Thumb code bytes and a 0x03002810 literal. */
void func_0804413C(void)
{
    g_state_03002810->panel->state = 4;
}
