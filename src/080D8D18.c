#include "ffta.h"

extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801CA78(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output,
                         s16 *third_output);
extern void func_080A92E4(s32 mode, s32 x, s32 height, s32 y, s32 effect);

/* Complete target: [0x080D8D18, 0x080D8D76), 94 bytes. */
void func_080D8D18(u8 column, u8 row)
{
    s16 x, height, y;
    u8 tile_height;

    tile_height = func_0801CC18(column, row);
    func_0801CA78(column, tile_height, row, &x, &height, &y);
    func_080A92E4(0, x, height, y, 0x15);
}
