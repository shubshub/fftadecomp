#include "ffta.h"

typedef struct {
    u16 value;
    u16 kind;
} MenuRecord;

typedef struct {
    u8 unknown_000[0x53C];
    MenuRecord records[1];
} MenuData;

typedef struct {
    MenuData *data;
    u16 flags;
    s16 selection;
    u8 slot;
    u8 unknown_09[0x59];
    u16 value;
    u8 unknown_64[0x15];
    u8 kind;
} MenuState;

typedef struct {
    u16 code;
    u8 unknown_02[0x12];
    u16 slot;
} MenuEvent;

extern MenuData *data_0201F548;
extern void func_0804ED6C(MenuState *state);
extern u8 func_0804EF68(MenuState *state);
extern u8 func_08050E14(MenuState *state);
extern u8 func_0804F0F4(MenuState *state);
extern u8 func_0804F14C(MenuState *state);
extern void func_0804F060(MenuState *state);
extern void func_0804F370(MenuState *state);
extern void func_08050E1C(MenuState *state);
extern void func_08050DE8(MenuState *state);
extern u8 func_0804EF90(MenuState *state);
extern void func_08050E28(MenuState *state);

/* Complete target: [0x0804E408, 0x0804E5CC), 452 bytes. */
u32 func_0804E408(void *context, MenuEvent *event, MenuState *state)
{
    switch (event->code) {
    case 0:
        state->slot = event->slot;
        state->data = data_0201F548;
        break;
    case 0x100:
        func_0804ED6C(state);
        event->code = 0x101;
        break;
    case 0x101:
        if (func_0804EF68(state)) {
            if (func_08050E14(state))
                event->code = 0x105;
            else
                event->code = 0x103;
        }
        break;
    case 0x107:
        if (func_0804F0F4(state))
            event->code = 0x103;
        break;
    case 0x103:
        if (func_0804F14C(state)) {
            switch (state->selection) {
            case -4:
                func_0804F060(state);
                state->selection = 0;
                event->code = 0x107;
                break;
            case -3:
                state->selection = 0;
                event->code = 0x106;
                break;
            default:
                {
                    MenuRecord *record = &state->data->records[state->slot];
                    record->value = state->value;
                    record->kind = state->kind;
                    event->code = 0x105;
                }
                break;
            }
        }
        func_0804F370(state);
        break;
    case 0x106:
        func_08050E1C(state);
        func_0804F370(state);
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
    if (event->code > 0x100)
        func_08050E28(state);
    return 0;
}
