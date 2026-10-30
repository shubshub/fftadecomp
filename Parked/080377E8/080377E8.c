#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u16 first_tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 map_stride;
    u8 unknown_29[3];
    u8 tile_stride;
    u8 unknown_2D[0x1F];
} TileLayout080377E8;

typedef struct {
    u8 unknown_000[0xC4C];
    u8 text_state[1];
} MenuState080377E8;

extern TileLayout080377E8 data_030009E0[];
extern u8 data_02003CB0[];
extern MenuState080377E8 *g_state_03002810;
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u8 *func_0808B92C(u32 index, u8 *tiles, u32 column, u32 row);
extern u8 func_080CB9CC(u16 graphic);
extern void func_080CB9B0(void *object, u32 graphic);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08015110(void *context, void *tiles, const void *text,
                          u32 mode, u32 spacing);

/* 0x080377E8..0x080378C8: 224 bytes, 98 instructions. */
void func_080377E8(u32 index, u8 *tiles, s32 x, s32 y,
                  u16 graphic, const void *text)
{
    u16 *map = func_0808B8E4(index, 1, x + 1, y + 2);
    TileLayout080377E8 *layout = &data_030009E0[index];
    u16 tile = layout->tile_stride * y + layout->first_tile + x * 2;
    u16 palette = func_080CB9CC(graphic) << 12;
    u8 *destination;

    map[0] = tile++ | palette;
    map[1] = tile++ | palette;
    map[layout->map_stride] = tile++ | palette;
    map[layout->map_stride + 1] = tile | palette;

    func_080CB9B0(data_02003CB0, (u8)graphic);
    destination = func_0808B92C(index, tiles, x, y);
    func_0814186C(data_02003CB0, destination, 0x40);
    destination += 0x80;
    func_08015110(g_state_03002810->text_state, destination,
                  text, 0, 1);
}
