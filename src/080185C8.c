#include "ffta.h"

typedef struct PanelResource080185C8 {
    u8 unknown_00[0x10];
    u8 *graphics;
    u16 *map;
} PanelResource080185C8;

typedef struct PanelContext080185C8 {
    PanelResource080185C8 *resource;
    void *secondary;
    u8 unknown_08[4];
    u16 tile;
    u8 unknown_0E[0x2C2];
    void *buffer;
    u8 *tile_graphics;
    u8 unknown_2D8[0x100];
} PanelContext080185C8;

typedef void (*BufferInitializer080185C8)(void *destination, u32 size);

extern PanelContext080185C8 *data_02009190;
extern BufferInitializer080185C8 const g_callbacks_0836D4B8[];

/* Complete [0x080185C8, 0x08018624): 92 bytes, 40 instructions. */
void func_080185C8(PanelContext080185C8 *context, void *buffer,
                   PanelResource080185C8 *resource, void *secondary, u16 tile)
{
    data_02009190 = context;
    g_callbacks_0836D4B8[0](data_02009190, sizeof(*data_02009190));
    data_02009190->resource = resource;
    data_02009190->secondary = secondary;
    data_02009190->tile = tile;
    data_02009190->buffer = buffer;
    data_02009190->tile_graphics = resource->graphics + tile * 32;
}
