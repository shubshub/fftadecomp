#include "ffta.h"

// 0x08038ECC..0x080391C0: 756 bytes, 325 instructions.

typedef struct {
    u8 flags;
    u8 unknown_01[7];
    const u8 *text;
} Row08038ECC;

typedef struct {
    u8 unknown_000[0x4DD];
    u8 count_4DD;
    u8 unknown_4DE[0x142];
    Row08038ECC rows[7];
    u8 unknown_674[0x5D8];
    u8 text_state[1];
    u8 unknown_C4D[0x2D2];
    u8 count_F1F;
} State08038ECC;

extern State08038ECC *g_state_03002810;
extern const u16 *const data_08391D44[];
extern const u16 *const data_08391D6C[];
extern const u16 *const data_08391D94[];
extern const u16 *const data_08391DBC[];

extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_080355E4(const u16 *source, u16 *destination, u32 height,
                          u16 width, u16 stride, u16 offset);
extern void func_08035638(const u16 *source, u16 *destination, u32 height,
                          u16 width, u16 stride, u16 value);
extern void func_08141868(const void *source, void *destination, u32 control);
extern u16 func_08015110(void *drawing, void *tiles, const u8 *text,
                         u8 palette, u8 reset);

void func_08038ECC(void)
{
    s32 i;
    u16 tile;
    u16 *map;
    u8 *tiles;
    s32 j;
    u32 zero;

    for (i = 0; i < 7; i++) {
        if (i >= g_state_03002810->count_F1F
            && i < g_state_03002810->count_F1F + g_state_03002810->count_4DD) {
            func_080355E4(data_08391D44[g_state_03002810->rows[i].flags], func_0808B8E4(4, 0, 0, i * 2 + 2),
                          2, 0xF, 0x1B, 0x56);
            if (i + 1 == g_state_03002810->count_F1F + g_state_03002810->count_4DD) {
                func_080355E4(data_08391D6C[g_state_03002810->rows[i].flags],
                          func_0808B8E4(4, 0, 0xC, i * 2 + 2), 2, 0xF, 0x1B, 0x56);
            } else {
                func_080355E4(data_08391D94[g_state_03002810->rows[i].flags],
                          func_0808B8E4(4, 0, 0xC, i * 2 + 2), 2, 0xF, 0x1B, 0x56);
            }
            tile = i * 28 + 0x18F;
            tile += (g_state_03002810->rows[i].flags & 1) ? 0x4000 : 0x9000;
            map = func_0808B8E4(4, 1, 0xD, i * 2 + 2);
            for (j = 0; j < 14; j++) {
                map[j] = tile++;
                map[j + 0x1B] = tile++;
            }
            tiles = (u8 *)0x0600B1E0 + i * 0x380;
            zero = 0;
            func_08141868(&zero, tiles, 0x010000E0);
            if (g_state_03002810->rows[i].flags & 2)
                tiles = (u8 *)0x0600B260 + i * 0x380;
            func_08015110(g_state_03002810->text_state, tiles,
                          g_state_03002810->rows[i].text, 0, 1);
        } else {
            func_08035638(data_08391D44[g_state_03002810->rows[i].flags], func_0808B8E4(4, 0, 0xC, i * 2 + 2),
                          2, 0xF, 0x1B, 0);
            func_080355E4(data_08391D44[g_state_03002810->rows[i].flags], func_0808B8E4(4, 0, 0, i * 2 + 2),
                          2, 0xF, 0x1B, 0x56);
            map = func_0808B8E4(4, 1, 0xD, i * 2 + 2);
            for (j = 0; j < 14; j++) {
                map[j] = 0;
                map[j + 0x1B] = 0;
            }
        }
        if (g_state_03002810->count_F1F
            && i + 1 == g_state_03002810->count_F1F) {
            func_080355E4(data_08391DBC[g_state_03002810->rows[i].flags], func_0808B8E4(4, 0, 0xC, i * 2 + 3),
                          1, 0xF, 0x1B, 0x56);
        }
    }
}
