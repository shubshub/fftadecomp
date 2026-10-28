#include "ffta.h"

typedef struct {
    u16 *first;
    u16 *second;
    u8 unknown_08[8];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_14[2];
    u8 kind;
    u8 unknown_17[5];
    u8 flags;
    u8 unknown_1d[3];
    u16 current_x;
    u16 current_y;
    s16 target_x;
    s16 target_y;
} BufferState;

typedef struct {
    u8 unknown_00[0x14];
    u16 *map;
} Resource;

typedef struct {
    Resource *resource;
    u8 unknown_04[5];
    u8 width;
    u8 column;
    s8 row;
    u16 tile;
    u8 flags;
    u8 unknown_0f;
    u8 height;
    u8 unknown_11[3];
    BufferState window;
} Context;

extern Context *data_02009190;
extern u8 func_080172F0(BufferState *state);
extern void func_080157A8(u16 *map, u8 column, u8 row, u8 width,
                          u8 height, u8 stride, u16 tile, u8 palette);

/* 080189A0..08018A0C: 108 bytes, 48 instructions. */
u8 func_080189A0(void)
{
    u8 result = func_080172F0(&data_02009190->window);

    if (result != 0) {
        Context *context = data_02009190;
        u16 *map = context->resource->map;
        u8 column = context->column + 1;
        s32 base_row = context->row;
        u8 row;

        if (context->flags & 2)
            row = base_row + 1;
        else
            row = base_row;
        func_080157A8(map, column, row, data_02009190->width,
                      data_02009190->height, 32, data_02009190->tile, 11);
    }
    return result;
}
