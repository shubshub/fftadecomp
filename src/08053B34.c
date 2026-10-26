#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 count;
    u8 unknown_16[6];
    u16 tile;
    u8 unknown_1E;
    u8 tag;
} TileRun;

typedef struct {
    u16 *map;
    u8 unknown_04[0x0C];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
    TileRun run;
} MenuState;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState;

extern TileState data_030008B0;
extern const u8 *const data_083937F8[];
extern void func_08013A88(void *destination, u32 rows);
extern void func_08015110(void *text_state, void *tiles, const u8 *text,
                        u32 style, u32 spacing);
extern void func_0802979C(void *text_state, void *tiles, u8 number,
                        u32 digits, u32 style);
extern void func_0802AB64(TileRun *run, u16 index, u16 value, u8 offset,
                        u8 count, u16 tag, u8 flag);
extern void func_0802AC14(MenuState *state, u16 *source,
                        u8 offset, u8 base, u8 count);

/* Complete target: [0x08053B34, 0x08053BE0), 172 bytes. */
void func_08053B34(MenuState *state, void *text_state, u8 number)
{
    u8 *tiles = data_030008B0.tiles + state->run.tile * 32;

    func_08013A88(tiles, state->run.count * 2);
    func_08015110(text_state, tiles, data_083937F8[0], 5, 1);
    tiles += 0x1C0;
    func_0802979C(text_state, tiles, number, 2, 5);
    func_0802AB64(&state->run, 0, state->run.tile, state->width,
                   state->run.count, state->run.tag, 1);
    func_0802AC14(state, state->run.tiles, (u8)(state->x + 1),
                   state->y, state->height);
}
