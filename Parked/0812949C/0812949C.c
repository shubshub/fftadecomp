#include "ffta.h"

/* Target: complete [0x0812949C, 0x081295C8), 300 bytes including literals. */
typedef struct {
    u8 unknown_00[0x28];
    u8 text_state[0x37e];
    u8 delay;
    u8 unknown_3a7;
    u8 text[0];
} State0812949C;

typedef struct {
    u8 unknown_00[0x10];
    u16 *tiles;
    u16 *tilemap;
} Graphics0812949C;

extern Graphics0812949C data_030008B0;
extern u16 func_08128FC4(State0812949C *);
extern void func_08013A88(void *, u32);
extern void *func_08121B64(u32);
extern void func_080CB980(void *, u32);
extern u32 func_080CB99C(u32);
extern u16 func_080161A0(u8, u8, u8);
extern void func_0814186C(const void *, void *, u32);
extern void func_08121B78(void *);
extern void func_08015110(void *, void *, const void *, u32, u32);
extern void func_0801539C(void *, void *, const void *, u32, u32);
extern void func_08141570(u32, u32);

u32 func_0812949C(State0812949C *state)
{
    u16 code;
    u16 *tiles;
    u16 *icon;
    u16 index;
    u16 *tilemap;

    if (state->delay) {
        state->delay--;
        return 0;
    }
    code = func_08128FC4(state);
    tiles = data_030008B0.tiles + 0x1b00;
    func_08013A88(tiles, 28);
    if (code) {
        icon = func_08121B64(128);
        if ((code & 0xf000) == 0x1000) {
            index = code & 0x0fff;
        } else if ((code & 0xf000) == 0x2000) {
            index = 0x188;
        } else {
            index = code & 0x0fff;
        }
        func_080CB980(icon, index);
        index = (u8)(func_080CB99C(index) + 13);
        tilemap = data_030008B0.tilemap + func_080161A0(10, 9, 32);
        tilemap[0] = 0x1b0 | (index << 12);
        tilemap[1] = 0x1b1 | (index << 12);
        tilemap[32] = 0x1b2 | (index << 12);
        tilemap[33] = 0x1b3 | (index << 12);
        func_0814186C(icon, tiles, 64);
        tiles += 64;
        func_08121B78(icon);
        func_08015110(state->text_state, tiles, state->text, 0, 1);
    } else {
        func_0801539C(state->text_state, tiles, state->text, 0, 14);
    }
    func_08141570(1, 123);
    return 1;
}
