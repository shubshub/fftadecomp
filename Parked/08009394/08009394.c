/* 0x08009394..0x08009412: 126 target bytes, including an internal literal. */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    void *owner;
    u16 field_08;
    u16 field_0a;
    u16 field_0c;
    u16 unknown_0e;
    u8 field_10;
    u8 unknown_11;
    u8 field_12;
} State08017FB0;

typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[3];
    u8 field_15;
} Struct08017AF4;

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

typedef struct {
    u8 unknown_00[0x2f0];
    u8 control[0x20];
    State08017FB0 panel;
    State08017FB0 menu;
} State08009394;

void func_08017FBC(State08017FB0 *panel, u8 value);
void func_08017FB0(State08017FB0 *panel, u8 value);
void func_08008F94(s8 index);
void func_08017884(void *state, u32 step);
void func_08017AF4(Struct08017AF4 *state, u8 index, u8 mode);
u16 func_08017B68(ClampState08017B68 *state, u32 index);
void func_08009414(u8 index);

void func_08009394(u8 step, u8 selection, u8 redraw)
{
    State08009394 *state = *(State08009394 **)0x02009188;
    State08017FB0 *panel = &state->panel;
    u8 *control = state->control;

    func_08017FBC(&state->menu, step);
    if (redraw == 0) {
        func_08017FB0(panel, selection);
    } else {
        func_08008F94((s8)selection);
        func_08017884(control, step);
    }
    func_08017AF4((Struct08017AF4 *)control, panel->unknown_11, 11);
    func_08009414(func_08017B68((ClampState08017B68 *)control,
                              (s8)panel->unknown_11));
}
