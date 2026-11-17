#include "ffta.h"

// Target: complete [0x0801E458, 0x0801E54C), 244 bytes, 122 instructions.

typedef struct {
    u8 unknown_00[0x0C];
    u8 width;
    u8 height;
    u8 unknown_0E[2];
    u32 tiles;
    u32 palette;
} Layer0801E458;

typedef struct {
    Layer0801E458 *layers[4];
} Layers0801E458;

extern const u16 g_object_08149914[];
extern const u16 g_object_0814991C[];
extern const Layers0801E458 g_object_08149924;
extern u16 data_0836DA94[];
extern u16 data_0836DA9C[];
extern void *func_081443FC(void *destination, const void *source, u32 byte_count);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);

void func_0801E458(u8 layer, u8 size, u8 priority, u16 x, u16 y,
                   u32 tiles, u32 palette)
{
    u16 sizes[4];
    u16 priorities[4];
    Layers0801E458 layers;
    Layer0801E458 *state;
    u32 attributes;
    u32 character;

    func_081443FC(sizes, g_object_08149914, sizeof(sizes));
    func_081443FC(priorities, g_object_0814991C, sizeof(priorities));
    layers = g_object_08149924;
    attributes = func_08003A74(palette);
    character = func_08003A80(tiles);
    attributes |= sizes[size];
    func_080034B8(attributes | character | priorities[priority], layer);
    func_08003508((s16)x, layer);
    func_08003558((s16)y, layer);
    state = layers.layers[layer];
    state->width = data_0836DA94[size] >> 3;
    state->height = data_0836DA9C[size] >> 3;
    state->tiles = tiles;
    state->palette = palette;
}
