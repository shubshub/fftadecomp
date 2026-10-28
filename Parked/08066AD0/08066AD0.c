#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

typedef struct {
    u8 unknown_00[4];
    u16 flags;
    u16 unknown_06;
    u8 mode;
    u8 active;
    u16 result;
} Menu;

typedef struct {
    u8 unknown_00[0x10];
    u8 selected;
    u8 count;
} SelectionState;

extern InputState data_03000000;
extern SelectionState g_state_020020D0;
extern void func_08141570(u32 channel, u32 sound);
extern void func_08141540(u32 sound);
extern void func_08013364(void);
extern void func_08011B30(u32 kind, u32 selection);

/* Complete target: [0x08066AD0, 0x08066BC4), 244 bytes, 102 instructions. */
u32 func_08066AD0(Menu *menu)
{
    u32 changed = 0;
    u16 pressed = data_03000000.pressed;

    if (pressed & 2) {
        u16 flags;
        if (menu->mode != 10)
            func_08141570(1, 0x69);
        func_08013364();
        menu->active = 0;
        menu->result = 0xFFFF;
        if (menu->mode == 10) {
            flags = menu->flags;
            flags |= 0x100;
        } else {
            flags = menu->flags;
            flags |= 0x40;
        }
        menu->flags = flags;
        goto handled;
    } else if (pressed & 1) {
        if (menu->mode != 10)
            func_08141540(0x64);
        func_08013364();
        menu->active = 0;
        menu->result = 0xFFFE;
        if (menu->mode == 10)
            menu->flags |= 0x100;
        else
            menu->flags |= 0x40;
        goto handled;
    } else if (pressed & 0x10) {
        changed = 1;
        if (g_state_020020D0.selected < g_state_020020D0.count - 1)
            g_state_020020D0.selected++;
        else
            g_state_020020D0.selected = 0;
    } else if (pressed & 0x20) {
        u32 selected;
        changed = 1;
        selected = g_state_020020D0.selected;
        if (selected == 0)
            selected = g_state_020020D0.count;
        g_state_020020D0.selected = selected - 1;
    }
    if (!changed)
        return 0;
    func_08141540(0x6D);
    func_08013364();
    func_08011B30(9, g_state_020020D0.selected);
handled:
    return 1;
}
