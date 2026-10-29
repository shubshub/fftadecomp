#include "ffta.h"

struct Menu0805DAA8 {
    u8 unknown_0000[0x794];
    u8 context[0xa05];
    u8 state;
    u8 transition;
    u8 action;
    u8 unknown_119c;
    u8 message;
    u8 unknown_119e;
    u8 enabled;
    u8 exit_requested;
    u8 pending;
    u8 unknown_11a2[0x2ae];
    const void *identifier;
};

struct Selection0805DAA8 {
    void *resource;
    u8 unknown_04[12];
    u8 selection;
    u8 count;
    u8 mode;
};

struct Input0805DAA8 {
    u16 held;
    u16 pressed;
};

extern struct Menu0805DAA8 *data_0200F448;
extern struct Selection0805DAA8 g_state_020020D0;
extern struct Input0805DAA8 data_03000000;
extern void func_08061564(void *context, u8 index);
extern void func_08141570(u32 channel, u32 sound);
extern void func_08141540(u32 sound);
extern void func_08013364(void);
extern u32 func_0805D1C0(u8 option);
extern s32 func_080D2E78(const void *identifier);
extern void func_08011B30(u32 window, u32 selection);

/* Complete [0x0805DAA8, 0x0805DD0C): 612 bytes, 232 instructions. */
void func_0805DAA8(u8 option)
{
    u32 changed = 0;
    u16 keys = data_03000000.pressed;

    data_0200F448->enabled = 1;
    if (g_state_020020D0.count == 4) {
        if (option == 0) {
            if (keys & 1) {
                data_0200F448->enabled = 0;
                func_08061564(data_0200F448->context, 2);
                data_0200F448->transition = 13;
                data_0200F448->state = 2;
                return;
            } else if (keys & 2) {
                func_08141570(1, 0x69);
                func_08013364();
                data_0200F448->enabled = 0;
                data_0200F448->message = func_0805D1C0(1);
                data_0200F448->action = 9;
                data_0200F448->transition = 18;
                data_0200F448->state = 2;
                return;
            }
        } else if (keys & 1) {
            if (func_080D2E78(data_0200F448->identifier)) {
                func_08061564(data_0200F448->context, 3);
                data_0200F448->transition = 13;
                data_0200F448->state = 2;
            } else {
                func_08141540(0x64);
                func_08013364();
                data_0200F448->transition = 0;
                data_0200F448->state = 2;
            }
            data_0200F448->enabled = 0;
            return;
        }
    }

    if (keys & 2) {
        func_08141570(1, 0x69);
        data_0200F448->pending = 0;
        data_0200F448->exit_requested = 1;
        func_08013364();
        data_0200F448->enabled = 0;
        data_0200F448->transition = 0;
        data_0200F448->state = 2;
    } else if (keys & 1) {
        func_08141540(0x64);
        func_08013364();
        data_0200F448->enabled = 0;
        data_0200F448->transition = 6;
        data_0200F448->state = 2;
    } else if (keys & 0x10) {
        changed = 1;
        if (g_state_020020D0.selection < g_state_020020D0.count - 1)
            ++g_state_020020D0.selection;
        else
            g_state_020020D0.selection = 0;
    } else if (keys & 0x20) {
        changed = 1;
        if (g_state_020020D0.selection == 0)
            g_state_020020D0.selection = g_state_020020D0.count - 1;
        else
            --g_state_020020D0.selection;
    }

    if (changed) {
        func_08141540(0x6d);
        func_08013364();
        func_08011B30(9, g_state_020020D0.selection);
        data_0200F448->transition = 5;
        data_0200F448->state = 2;
    }
}
