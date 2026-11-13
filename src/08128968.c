#include "ffta.h"

// func_08128968 [0x08128968,0x08128B4C) 484 bytes including literals

typedef struct {
    u16 identifier : 4;
    u16 job : 7;
    u16 alternate : 1;
    u16 unknown_0C : 4;
} __attribute__((packed)) Key08128968;

typedef struct Unit08128968 {
    u8 unknown_00[9];
    u8 level;
} Unit08128968;

typedef struct State08128968 {
    u8 unknown_00[8];
    Unit08128968 *unit;
    Key08128968 *key;
    u8 unknown_10[0x18];
    u8 text[0x290];
    u16 *tilemap;
} State08128968;

typedef struct {
    u8 unknown_00[0x10];
    u8 *destination;
} Destination08128968;

extern Destination08128968 data_030008B0;
extern const u8 *const g_table_08526680[];
extern void func_080157A8(u16 *tilemap, u8 column, u8 row, u8 width,
    u8 height, u8 stride, u16 tile, u8 palette);
extern void func_08015110(void *context, void *tiles, const void *text,
    u32 style, u32 spacing);
extern void func_0801539C(void *context, void *tiles, const void *text,
    u32 style, u32 count);
extern s32 func_080C7EA4(const void *unit, u32 selector);
extern u32 func_080C92F0(void *unit, u32 selector);
extern u32 func_08142AB0(u32 value, u32 divisor);
extern u32 func_08142B28(u32 value, u32 divisor);

void func_08128968(State08128968 *state)
{
    Unit08128968 *unit = state->unit;
    u16 *tilemap = state->tilemap;
    u16 *cell = tilemap + 0x28;
    u32 palette;
    u8 tens;

    palette = state->key->alternate ? 14 : 15;
    palette <<= 12;
    cell[0] = palette | 0x17A;
    cell[1] = palette | 0x17B;
    cell[0x13] = palette | 0x17C;
    cell[0x14] = palette | 0x17D;

    cell = tilemap;
    func_080157A8(cell, 4, 2, 12, 1, 19, 0x180, 11);
    func_08015110(state->text, data_030008B0.destination + 0x3000,
        g_table_08526680[state->key->job + 0x271], 0, 1);
    func_080157A8(cell, 4, 5, 12, 1, 19, 0x198, 10);
    func_080157A8(cell, 4, 7, 14, 1, 19, 0x1B0, 12);
    func_080157A8(cell, 2, 11, 12, 1, 19, 0x1CC, 12);
    func_0801539C(state->text, data_030008B0.destination + 0x3980,
        (const void *)func_080C7EA4(unit, 0), 0, 12);
    func_080157A8(cell, 2, 13, 12, 1, 19, 0x1E4, 12);
    func_0801539C(state->text, data_030008B0.destination + 0x3C80,
        g_table_08526680[func_080C92F0(unit, 0)], 0, 12);

    cell = tilemap + 0x12B;
    *cell = 0xC0BA;
    cell = tilemap + 0x12C;
    *cell = 0xC0BB;
    cell = tilemap + 0x12D;
    tens = func_08142AB0(unit->level, 10);
    if (tens)
        *cell = (tens + 30) | 0xD000;
    cell = tilemap + 0x12E;
    *cell = (u8)func_08142B28(unit->level, 10) + 30 | 0xD000;
}
