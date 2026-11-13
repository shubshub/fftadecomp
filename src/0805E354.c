#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1199];
    u8 phase;
    u8 action;
    u8 unknown_119B;
    u8 cancel_phase;
    u8 unknown_119D[6];
    u8 selection;
    u8 unknown_11A4[6];
    u8 entry_count;
    u8 unknown_11AB[0x9D];
    void *entries[130];
    void *selected;
    void *pending;
} MenuState;

typedef struct {
    u8 unknown_00[0x10];
    u8 selection;
    u8 mode;
} MenuContext;

typedef struct {
    u16 unknown_00;
    u16 pressed;
} InputState;

extern MenuState *data_0200F448;
extern MenuContext g_state_020020D0;
extern InputState data_03000000;
extern u8 func_08060DD4(void);
extern s16 func_08060DC4(void);
extern void func_0805F4D8(u8 kind, u8 enabled);
extern void func_0806144C(u8 enabled);
extern void func_08013364(void);
extern void func_080610F8(u8 message);
extern u32 func_0805D1C0(u8 option);
extern void func_08060E24(u8 selection);
extern void func_0805DDC8(u16 index);
extern void func_0805F540(void *const *entries, s32 count);
extern void func_0805F59C(u8 kind, s16 selection);

/* Complete target: [0x0805E354, 0x0805E5C0), 620 bytes. */
u32 func_0805E354(void)
{
    s16 selection;

    switch (func_08060DD4()) {
    case 1:
    case 2:
        if (g_state_020020D0.mode == 4) {
            g_state_020020D0.selection = 0;
            g_state_020020D0.mode = 3;
        }
        func_0805F4D8(5, 1);
        func_0806144C(0);
        if (data_0200F448->pending != 0) {
            data_0200F448->action = 20;
            data_0200F448->phase = 1;
        } else {
            data_0200F448->action = 12;
            data_0200F448->phase = 1;
        }
        return 1;
    case 3:
    case 4:
        selection = func_08060DC4();
        if (selection < 0) {
            switch (data_0200F448->cancel_phase) {
            case 0:
                func_08013364();
                func_080610F8(0x50);
                data_0200F448->cancel_phase = 1;
                data_0200F448->action = 10;
                data_0200F448->phase = 3;
                break;
            case 1:
                if (data_03000000.pressed & 3) {
                    func_08013364();
                    func_080610F8(func_0805D1C0(0));
                    data_0200F448->cancel_phase = 2;
                    data_0200F448->action = 10;
                    data_0200F448->phase = 3;
                }
                break;
            default:
                func_0805F4D8(5, 0);
                data_0200F448->cancel_phase = 0;
                data_0200F448->action = 10;
                data_0200F448->phase = 1;
                break;
            }
        } else {
            if (selection <= 1) {
                data_0200F448->selection = selection;
                func_08060E24(data_0200F448->selection);
                func_08013364();
                data_0200F448->action = 11;
                data_0200F448->phase = 3;
            } else {
                g_state_020020D0.selection = 3;
                g_state_020020D0.mode = 4;
                func_0805F4D8(5, 1);
                data_0200F448->action = 12;
                data_0200F448->phase = 1;
            }
            func_0806144C(0);
        }
        return 1;
    case 6:
        selection = func_08060DC4();
        if (selection <= 1) {
            func_0805DDC8(selection);
            func_0805F540(data_0200F448->entries,
                         data_0200F448->entry_count + 2);
            func_0805F59C(5, selection);
            if (selection != 2 &&
                data_0200F448->entries[data_0200F448->entry_count + selection] == 0)
                func_0806144C(0);
            data_0200F448->action = 10;
            data_0200F448->phase = 1;
        }
        return 1;
    default:
        break;
    }
    return 0;
}
