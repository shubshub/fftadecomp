#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u8 text[0x2C0 - 0x28];
    const u8 *script;
    u8 unknown_2C4[0x3A6 - 0x2C4];
    u8 delay;
    u8 unknown_3A7;
    u8 line[0];
} State0812949C;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
    u16 *tilemap;
} Graphics0812949C;

extern Graphics0812949C data_030008B0;
extern u16 func_08128FC4(State0812949C *state);
extern void func_08013A88(void *destination, u16 count);
extern void *func_08121B64(u32 size);
extern void func_080CB980(void *object, u32 value);
extern u8 func_080CB99C(u16 index);
extern u16 func_080161A0(u8 x, u8 y, u8 width);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08121B78(u8 *object);
extern u16 func_08015110(void *state, void *buffer, const u8 *text,
                         u8 style, u8 mode);
extern u16 func_0801539C(void *state, void *buffer, const u8 *text,
                         u8 style, u8 width);
extern void func_08141570(s32 player_id, u16 song_id);

/* Complete [0x0812949C, 0x081295C8): 300 bytes, 127 instructions.
 * Once the delay has run out, asks func_08128FC4 for the next line and draws
 * it at tile 0x1B0; a nonzero result code selects an icon to draw before the
 * text.  func_08128FC4 returns 0, an icon number tagged 0x1000, or 0x2000. */
u32 func_0812949C(State0812949C *state)
{
    u16 code;
    u8 *tiles;
    u8 *icon;
    u8 palette;
    u16 *tilemap;

    if (state->delay) {
        state->delay--;
        return 0;
    }
    code = func_08128FC4(state);
    tiles = data_030008B0.tiles + 0x3600;
    func_08013A88(tiles, 28);
    if (code) {
        icon = func_08121B64(0x80);
        switch (code & 0xf000) {
        case 0x2000:
            func_080CB980(icon, 0x188);
            palette = func_080CB99C(0x188) + 13;
            break;
        case 0x1000:
        default:
            func_080CB980(icon, code & 0x0fff);
            palette = func_080CB99C(code & 0x0fff) + 13;
            break;
        }
        tilemap = data_030008B0.tilemap + func_080161A0(10, 9, 32);
        tilemap[0] = 0x1b0 | (palette << 12);
        tilemap[1] = 0x1b1 | (palette << 12);
        tilemap[32] = 0x1b2 | (palette << 12);
        tilemap[33] = 0x1b3 | (palette << 12);
        func_0814186C(icon, tiles, 0x40);
        tiles += 0x80;
        func_08121B78(icon);
        func_08015110(state->text, tiles, state->line, 0, 1);
    } else {
        func_0801539C(state->text, tiles, state->line, 0, 14);
    }
    func_08141570(1, 123);
    return 1;
}
