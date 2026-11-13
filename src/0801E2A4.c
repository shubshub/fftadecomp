#include "ffta.h"

// Target: complete [0x0801E2A4, 0x0801E458), 436 bytes, 218 instructions.
typedef struct {
    u8 unknown_00[0xC];
    u8 tile_x;
    u8 tile_y;
    u8 unknown_0E[2];
    u32 source_a;
    u32 source_b;
} Layer;

typedef struct {
    u8 layer_a;
    u8 layer_b;
    u8 offset_a;
    u8 offset_b;
    u8 index;
    u8 unknown_05[0xB];
    u32 source_a;
    u32 source_b;
    u32 source_c;
    u8 unknown_1C[8];
    s16 x;
    s16 y;
    s16 base_x;
    s16 base_y;
} Camera;

extern Camera g_state_02007F40;
extern const u8 data_08149914[];
extern const u8 data_0814991C[];
typedef struct { Layer *v[4]; } Layers;
extern const Layers data_08149924;
extern const u16 data_0836DA94[];
extern const u16 data_0836DA9C[];
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void func_080034B8(u16 control, u8 layer);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);

static inline void place(u8 layer, u8 index, u8 offset, s16 x, s16 y, u32 a, u32 b)
{
    u16 sizes[4];
    u16 modes[4];
    Layers layers;
    Layer *l;

    func_081443FC(sizes, data_08149914, sizeof(sizes));
    func_081443FC(modes, data_0814991C, sizeof(modes));
    layers = data_08149924;
    {
    u32 p = func_08003A74(b);
    u32 q = func_08003A80(a);
    u32 c = sizes[index];
    c |= p;
    c |= q;
    c |= modes[offset];
    func_080034B8(c, layer);
    }
    func_08003508(x, layer);
    func_08003558(y, layer);
    l = layers.v[layer];
    l->tile_x = data_0836DA94[index] >> 3;
    l->tile_y = data_0836DA9C[index] >> 3;
    l->source_a = a;
    l->source_b = b;
}

void func_0801E2A4(void)
{
    u16 dx = g_state_02007F40.x - g_state_02007F40.base_x;
    u16 dy = g_state_02007F40.y - g_state_02007F40.base_y;

    if ((g_state_02007F40.layer_a >> 7) != 1)
        place(g_state_02007F40.layer_a, g_state_02007F40.index, g_state_02007F40.offset_a, dx, dy,
              g_state_02007F40.source_a, g_state_02007F40.source_b);
    if ((g_state_02007F40.layer_b >> 7) != 1)
        place(g_state_02007F40.layer_b, g_state_02007F40.index, g_state_02007F40.offset_b, dx, dy,
              g_state_02007F40.source_a, g_state_02007F40.source_c);
}
