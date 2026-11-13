// Complete [0x08128B4C,0x08128C3C): 240 bytes, 117 instructions.
// Steps a text script: high-bit bytes are glyphs, 0x40 escapes move the cursor.
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u8 text[0x2C0 - 0x28];
    const u8 *script;
    u8 unknown_2C4[0x3A6 - 0x2C4];
    u8 delay;
    u8 unknown_3A7[0x3D6 - 0x3A7];
    u16 sound;
} State08128B4C;

extern void func_0801360C(void *text, s32 character);
extern void func_08013728(void *text, s16 amount);
extern void func_08141570(s32 player_id, u16 song_id);

u32 func_08128B4C(State08128B4C *state)
{
    const u8 *p;
    u8 c;

    if (state->delay != 0) {
        state->delay--;
        return 0;
    }
    state->delay = 10;

    p = state->script;
    c = p[0];
    if (c == 0)
        return 1;

    if (c & 0x80) {
        func_0801360C(state->text, (u16)((c << 8) | p[1]) & 0x7FFF);
        state->script += 2;
        func_08141570(1, state->sound++ + 0x1DD);
        if (state->sound > 2)
            state->sound = 0;
    } else if (c == 0x40) {
        switch (p[1]) {
        case 0x73:
            func_08013728(state->text, 6);
            state->script += 2;
            break;
        case 0x3C:
        case 0x3E: {
            u16 amount = state->script[2];

            if (state->script[1] == 0x3C)
                amount = -amount;
            func_08013728(state->text, amount);
            state->script += 3;
            break;
        }
        }
        state->delay = 0;
        func_08128B4C(state);
    }
    return 0;
}
