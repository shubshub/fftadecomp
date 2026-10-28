#include "ffta.h"

/* Complete target: [0x0804E858, 0x0804E990), 312 bytes. */
typedef struct MenuData MenuData;

typedef struct {
    MenuData *data;
    u16 flags;
    s16 selection;
    u8 slot;
} MenuState;

typedef struct {
    u16 code;
    u8 unknown_02[0x12];
    u16 slot;
} MenuEvent;

extern MenuData *data_0201F548;
extern void func_0804F5BC(MenuState *state);
extern u8 func_0804EF68(MenuState *state);
extern u32 func_08050E14(const MenuState *state);
extern u8 func_0804F744(MenuState *state);
extern void func_08050EFC(MenuState *state);
extern void func_08050DE8(MenuState *state);
extern u8 func_0804EF90(MenuState *state);
extern void func_0804F8A4(MenuState *state);

u32 func_0804E858(void *context, MenuEvent *event, MenuState *state)
{
    switch (event->code) {
    case 0:
        state->slot = event->slot;
        state->data = data_0201F548;
        break;
    case 0x100:
        func_0804F5BC(state);
        event->code = 0x101;
        break;
    case 0x101:
        if (func_0804EF68(state)) {
            if ((u8)func_08050E14(state))
                event->code = 0x105;
            else
                event->code = 0x103;
        }
        break;
    case 0x103:
        if (func_0804F744(state)) {
            if (state->selection == -3) {
                state->selection = 0;
                event->code = 0x106;
            } else {
                event->code = 0x105;
            }
        }
        break;
    case 0x106:
        func_08050EFC(state);
        event->code = 0x103;
        break;
    case 0x105:
        if (state->flags & 0x80) {
            state->flags &= ~0x80;
            event->code = 3;
        } else if (state->flags & 0x40) {
            state->flags &= ~0x40;
            func_08050DE8(state);
            event->code = 0x102;
        } else if (state->flags & 0x20) {
            state->flags &= ~0x20;
            event->code = 0x103;
        }
        break;
    case 0x102:
        if (func_0804EF90(state)) {
            state->selection = -2;
            event->code = 0x105;
        }
        break;
    case 1:
        break;
    }
    func_0804F8A4(state);
    return 0;
}
