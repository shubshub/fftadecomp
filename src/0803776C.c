#include "ffta.h"

struct MenuState0803776C {
    u8 unknown_000[0xc4c];
    u8 text_state[1];
};

extern u8 data_02003CB0[];
extern struct MenuState0803776C *g_state_03002810;
extern void func_080CB9B0(void *object, u32 value);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08015110(void *context, void *tiles, const void *text,
                          u32 mode, u32 spacing);

/* Complete [0x0803776C, 0x080377E8): 124 bytes, 52 instructions. */
void func_0803776C(u8 *tiles, u16 *map, u32 graphic, const u8 *text,
                  u16 tile, u32 stride)
{
    u8 *buffer = data_02003CB0;

    map[0] = tile++;
    map[1] = tile++;
    map[stride] = tile++;
    map[stride + 1] = tile;

    func_080CB9B0(buffer, (u8)graphic);
    func_0814186C(buffer, tiles, 0x40);
    func_08015110(g_state_03002810->text_state, tiles + 0x80, text, 0, 1);
}
