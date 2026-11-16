#include "ffta.h"

/* Complete [0x08038DCC, 0x08038ECC): 256 bytes, 110 instructions. */

/* The seven-entry display window at +0x620, as src/0803920C.c names it. */
typedef struct {
    u8 kind;
    u8 unknown_01[3];
    const u8 *first;
    const u8 *second;
} Display08038DCC;

typedef struct {
    u8 unknown_000[0x620];
    Display08038DCC display[7];
    u8 unknown_674[0x5D8];
    u8 text_state[1];
} State08038DCC;

extern State08038DCC *g_state_03002810;

extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_08141868(const void *source, void *destination, u32 control);
extern u16 func_08015110(void *context, void *tiles, const u8 *text,
    u8 mode, u8 reset);

void func_08038DCC(void)
{
    s32 i;
    u16 tile;
    u16 *map;
    u8 *tiles;
    s32 j;
    u32 zero;

    for (i = 0; i < 7; i++) {
        tile = i * 28 + 0xCB;
        tile += (g_state_03002810->display[i].kind & 1) ? 0x4000 : 0x5000;
        map = func_0808B8E4(4, 1, 1, i * 2 + 2);
        for (j = 0; j < 14; j++) {
            map[j] = tile++;
            map[j + 0x1B] = tile++;
        }
        /* VRAM tile addresses are plain numbers: the pool words at 0x08038EB4
         * and 0x08038EC0 carry no relocation, and naming them as data
         * symbols changes the register allocation (235/256 bytes). */
        tiles = (u8 *)0x06009960 + i * 0x380;
        zero = 0;
        func_08141868(&zero, tiles, 0x010000E0);
        if (g_state_03002810->display[i].kind & 2)
            tiles = (u8 *)0x060099E0 + i * 0x380;
        func_08015110(g_state_03002810->text_state, tiles,
            g_state_03002810->display[i].first, 0, 1);
    }
}
