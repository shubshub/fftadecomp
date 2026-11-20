#include "ffta.h"

typedef struct {
    u8 unknown_00[10];
    s8 x;
    s8 y;
} TilePosition;

extern u8 func_080DD698(void *object, u16 mask);
extern u8 func_080DD494(void *object);
extern TilePosition *func_080A880C(void *object);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801CA78(s16 column, s16 height, s16 row,
                         s16 *world_x, s16 *world_y, s16 *world_z);
extern void func_080A92E4(u16 mode, s16 x, s16 height, s16 y, s32 effect);
extern void func_08141570(s32 mode, u16 sound);
extern void func_08141520(u16 sound);

static inline void get_coordinates(void *object, s16 *x, s16 *y)
{
    TilePosition *position = func_080A880C(object);

    *x = position->x;
    *y = position->y;
}

static inline void emit_tile_effect(u8 column, u8 row)
{
    s16 x, height, y;
    u8 tile_height = func_0801CC18(column, row);

    func_0801CA78(column, tile_height, row, &x, &height, &y);
    func_080A92E4(0, x, height, y, 0x15);
}

static inline void play_effect_sound(u16 flags)
{
    s32 mode = 0;

    if (flags & 1)
        return;
    if (flags & 2)
        mode = 1;
    else if (flags & 4)
        mode = 2;
    if (mode != 0)
        func_08141570(mode, 0x8D);
    else
        func_08141520(0x8D);
}

u8 func_080D8858(void *object, u16 flags)
{
    s16 x, y;

    if (!func_080DD698(object, 0x20))
        return func_080DD494(object);

    get_coordinates(object, &x, &y);
    emit_tile_effect(x, y);
    play_effect_sound(flags);
    return 0;
}
