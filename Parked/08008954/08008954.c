/* 0x08008954..0x08008D4E: 1018 target bytes, including local table and literals. */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    void *owner;
    u16 position;
    u16 extent;
    u16 unknown_0c;
    u16 limit;
    u8 flags;
    u8 unknown_11[3];
} Panel08008954;

typedef struct {
    u32 unknown_00;
    u16 state;
    u16 depth;
    u16 history[8];
    u32 argument_18;
    u32 argument_1c;
    u8 handle;
    u8 unknown_21;
    u8 command;
    u8 unknown_23[0x299];
    u8 control_value;
    u8 unknown_2bd[7];
    u8 control[0x4c];
    Panel08008954 panel;
    Panel08008954 menu;
    u8 unknown_338[0xe90];
    u8 dialog[0xa04];
    u8 settings[4];
} State08008954;

extern u8 g_state_02000000[];
extern u8 g_state_020020D0[];
extern const u8 g_table_0851BA4E[];

void func_08008D50(void);
u16 func_08008E78(u32 context);
void func_08008E94(void);
u8 func_08009140(void);
void func_080096E0(void);
void func_08009728(void);
u8 func_080098F4(u16 (*callback)(u32), u32 context);
void func_08009920(u8 mode);
u8 func_080099A4(u8 handle);
void func_0801174C(void *dialog, u32 enabled, u8 command, u32 argument,
                   u32 second_argument, u32 first, u32 second, u32 width,
                   u32 height, u32 offset);
u16 func_08011860(void);
s8 func_08013380(void);
void func_0801339C(u16 value);
void func_08013404(u32 first, u32 second);
void func_08013428(s16 value);
void func_08016234(void *control);
void func_08017508(void *control, u8 value);
void func_08017D18(Panel08008954 *panel, u8 flags);
void func_08017E28(Panel08008954 *panel);
void *memcpy(void *destination, const void *source, unsigned long size);

u32 func_08008954(void)
{
    State08008954 **current = (State08008954 **)0x02009188;
    State08008954 *state;
    Panel08008954 *panel;
    Panel08008954 *menu;
    u8 selection;
    s16 result;
    u8 *settings;
    u8 *control_value;

    switch ((*current)->state) {
    case 0:
        func_08008D50();
        state = *current;
        state->state = 4;
        state->history[state->depth++] = state->state;
        state->state = 2;
        break;
    case 1:
        return 1;
    case 2:
        if (func_080099A4((*current)->handle)) {
            func_08008E94();
            state = *current;
            state->state = state->history[--state->depth];
        }
        break;
    case 3:
        if (func_080099A4((*current)->handle)) {
            (*current)->depth = 0;
            (*current)->state = 1;
        }
        break;
    case 4:
        selection = func_08009140();
        func_08016234((*current)->control);
        switch (selection) {
        case 0:
            break;
        case 2:
            (*current)->state = 6;
            break;
        case 3:
            (*current)->command = 0x1d;
            state = *current;
            state->state = 9;
            state->history[state->depth++] = state->state;
            state->state = 4;
            state->history[state->depth++] = state->state;
            state->state = 8;
            state->history[state->depth++] = state->state;
            state->state = 7;
            break;
        case 4:
            (*current)->command = 0x1e;
            state = *current;
            state->state = 10;
            state->history[state->depth++] = state->state;
            state->state = 6;
            state->history[state->depth++] = state->state;
            state->state = 8;
            state->history[state->depth++] = state->state;
            state->state = 7;
            break;
        default:
            state = *current;
            state->state = 4;
            state->history[state->depth++] = state->state;
            state->state = 5;
            break;
        }
        break;
    case 5:
        func_08017E28(&(*current)->menu);
        func_08016234((*current)->control);
        state = *current;
        state->state = state->history[--state->depth];
        break;
    case 6:
        control_value = &(*current)->control_value;
        func_08009920((g_state_02000000[0x2fc0] >> 1) & 3);
        func_08017508((*current)->control, *control_value);
        (*current)->handle = func_080098F4(func_08008E78, 0);
        (*current)->state = 3;
        break;
    case 7:
        state = *current;
        panel = &state->panel;
        menu = &state->menu;
        func_0801174C(state->dialog, 1, state->command, state->argument_18,
                       state->argument_1c, 2, 2, 24, 4, 0x3a0);
        func_0801339C(2);
        func_08013404((u32)func_080096E0, (u32)func_08009728);
        func_08013428(*(s16 *)(g_state_020020D0 + 0xb0));
        if (panel->extent + panel->limit <= 63)
            func_08017D18(panel, 0);
        else
            func_08017D18(panel, 1);
        if (menu)
            menu->flags = (menu->flags & ~4) | 0x40;
        func_08016234((*current)->control);
        state = *current;
        state->state = state->history[--state->depth];
        break;
    case 8:
        if (func_08011860()) {
            result = func_08013380();
            menu = &(*current)->menu;
            if (menu)
                menu->flags = (menu->flags & ~0x40) | 4;
            if (result < 0) {
                func_08017D18(&(*current)->panel, 7);
                (*current)->depth = 0;
                (*current)->state = 4;
            } else if (result > 0) {
                func_08017D18(&(*current)->panel, 7);
                state = *current;
                state->state = state->history[--state->depth];
                state->depth = 0;
            } else {
                state = *current;
                state->state = state->history[--state->depth];
                state->state = state->history[--state->depth];
            }
        }
        func_08016234((*current)->control);
        break;
    case 9:
        memcpy((*current)->settings, g_table_0851BA4E, 4);
        settings = g_state_02000000 + 0x2fc0;
        memcpy(settings, (*current)->settings, 4);
        func_08009920((settings[0] >> 1) & 3);
        func_08017D18(&(*current)->panel, 7);
        func_08016234((*current)->control);
        (*current)->depth = 0;
        (*current)->state = 6;
        break;
    case 10:
        settings = g_state_02000000 + 0x2fc0;
        memcpy(settings, (*current)->settings, 4);
        func_08009920((settings[0] >> 1) & 3);
        func_08016234((*current)->control);
        (*current)->depth = 0;
        (*current)->state = 6;
        break;
    }
    return 0;
}
