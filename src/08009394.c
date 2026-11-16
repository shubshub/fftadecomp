#include "ffta.h"

/* Target: [0x08009394, 0x08009412), 126 bytes, 53 instructions, including
   one internal literal word (data_02009188) after an alignment halfword. */

typedef struct {
    u8 unknown_00[0x15];
    u8 field_15;
    u8 unknown_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u16 field_1C;
} ClampState08017B9C;

typedef struct {
    u8 unknown_00[0x11];
    s8 selection;
} Panel08009394;

typedef struct {
    u8 unknown_000[0x2F0];
    ClampState08017B9C control;
    Panel08009394 panel;
    u8 unknown_324[0x14];
} State08009394;

extern State08009394 *data_02009188;

void func_08017FBC(void *settings, u32 direction);
void func_08017FB0(Panel08009394 *panel, u8 row);
void func_08008F94(s16 index);
void func_08017884(ClampState08017B9C *control, u32 direction, u32 mode);
void func_08017AF4(ClampState08017B9C *control, s8 position, u8 mode);
u16 func_08017B68(ClampState08017B9C *control, u32 index);
void func_08009414(u8 index);

void func_08009394(u8 direction, s8 position, u8 scroll)
{
    State08009394 *state = data_02009188;
    Panel08009394 *panel = &state->panel;
    u8 *settings = state->unknown_324;
    ClampState08017B9C *control = &state->control;

    func_08017FBC(settings, direction);
    if (scroll == 0) {
        func_08017FB0(panel, position);
    } else {
        func_08008F94(position);
        func_08017884(control, direction, 1);
    }
    func_08017AF4(control, panel->selection, 11);
    func_08009414(func_08017B68(control, panel->selection));
}
