#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 *base;
    u8 unknown_10[5];
    u8 count;
    u8 unknown_16[6];
    u16 tile;
    u8 unknown_1E;
    u8 tag;
} Panel080537A8;

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
    Panel080537A8 panel;
} Menu080537A8;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics080537A8;

extern Graphics080537A8 data_030008B0;
extern const u8 *data_083937F8[];
extern void func_08013A88(void *tiles, u32 count);
extern void func_08015110(void *context, u8 *tiles, const u8 *source,
                         u32 width, u32 height);
extern void func_0802979C(void *context, u8 *tiles, u8 color,
                         u32 width, u32 height);
extern void func_0802AB64(Panel080537A8 *panel, u16 index, u16 tile,
                         u8 offset, u8 count, u16 tag, u8 interleave);
extern void func_0802AC14(Menu080537A8 *menu, u16 *source,
                         u8 x, u8 y, u8 height);

/* 0x080537A8..0x0805391C: 372 bytes, including literal pools. */
void func_080537A8(Menu080537A8 *menu, void *context,
                   u8 first_color, u8 second_color, u8 rebuild)
{
    u8 *tiles;

    if (rebuild) {
        tiles = data_030008B0.tiles + menu->panel.tile * 32;
        func_08013A88(tiles, menu->panel.count * 2);
        func_08015110(context, tiles, data_083937F8[0], 5, 1);
        func_0802979C(context, tiles + 0x140, first_color, 2, 5);

        tiles = data_030008B0.tiles +
                (menu->panel.count * 64 + menu->panel.tile * 32);
        func_08013A88(tiles, menu->panel.count * 2);
        func_08015110(context, tiles, data_083937F8[1], 5, 1);
        func_0802979C(context, tiles + 0x140, second_color, 2, 5);

        func_0802AB64(&menu->panel, 0, menu->panel.tile, menu->width,
                      menu->panel.count, menu->panel.tag, 1);
        func_0802AB64(&menu->panel, menu->width * 2,
                      menu->panel.count * 2 + menu->panel.tile,
                      menu->width, menu->panel.count, menu->panel.tag, 1);
        func_0802AC14(menu, menu->panel.base, menu->x + 1,
                      menu->y, menu->height);
    } else {
        tiles = data_030008B0.tiles + menu->panel.tile * 32;
        func_0802979C(context, tiles + 0x140, first_color, 2, 5);

        tiles = data_030008B0.tiles +
                (menu->panel.count * 64 + menu->panel.tile * 32);
        func_0802979C(context, tiles + 0x140, second_color, 2, 5);
    }
}
