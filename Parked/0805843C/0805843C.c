#include "ffta.h"

/* 0x0805843C..0x08058608: 460 bytes. */
typedef struct {
    u8 unknown_00[0x15];
    u8 columns;
    u8 unknown_16[6];
    u16 tileIndex;
} NumberPanel;

typedef struct {
    u32 pixels[8];
} Tile;

typedef struct {
    u8 unknown_00[0x10];
    Tile *tiles;
} RenderState;

typedef struct {
    u8 unknown_00[0x70];
    const char *label;
    const char *secondaryLabel;
    u8 unknown_78[0xAF8];
    const char *suffix;
} PanelStrings;

typedef struct DrawContext DrawContext;

extern RenderState data_030008B0;
extern const PanelStrings g_table_085567F0;
extern const char data_08391784[];
extern const char data_08391787[];
extern const char data_083917C1[];
extern const char data_083917B8[];
extern void func_08013A88(Tile *, u32);
extern void func_08015110(DrawContext *, Tile *, const char *, s32, s32);
extern void func_0802979C(DrawContext *, Tile *, u32, s32, s32);
extern u8 func_08058608(u32);

void func_0805843C(NumberPanel *panel, DrawContext *context, u32 value,
    u8 secondary, u8 compact)
{
    Tile *tiles = data_030008B0.tiles + panel->tileIndex;
    u8 digits;
    const PanelStrings *strings = &g_table_085567F0;

    func_08013A88(tiles, panel->columns * 4);
    if (compact == 0) {
        func_08015110(context, tiles, strings->label, 5, 1);
        func_08015110(context, tiles + 14, data_08391784, 5, 1);
        digits = func_08058608(value);
        func_0802979C(context, tiles + 16, value, digits, 5);
        func_08015110(context, tiles + (digits * 2 + 16), strings->suffix, 5, 1);
    } else {
        func_08015110(context, tiles, strings->label, 5, 1);
        func_08015110(context, tiles + 6, data_08391784, 5, 1);
        digits = func_08058608(value);
        func_0802979C(context, tiles + 8, value, digits, 5);
        func_08015110(context, tiles + (digits * 2 + 8), strings->suffix, 5, 1);
    }
    tiles += panel->columns * 2;
    if (compact == 0) {
        func_08015110(context, tiles, strings->secondaryLabel, 5, 1);
        func_08015110(context, tiles + 14, data_08391784, 5, 1);
    } else {
        func_08015110(context, tiles, data_08391787, 5, 1);
    }
    if (compact == 0) {
        digits = func_08058608(secondary);
        func_0802979C(context, tiles + 16, secondary, digits, 5);
        func_08015110(context, tiles + (digits * 2 + 16), data_083917C1, 5, 1);
    } else {
        func_0802979C(context, tiles + 38, secondary, 2, 5);
        func_08015110(context, tiles + 42, data_083917B8, 5, 1);
    }
}
