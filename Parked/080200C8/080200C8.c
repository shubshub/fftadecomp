#include "ffta.h"
#include "control_flags.h"

typedef struct __attribute__((packed)) {
    u8 unknown_00[0x50];
    u32 layer_data_offset;
    u8 unknown_54[4];
} ResourceRecord;

typedef struct __attribute__((packed)) {
    u16 x, y;
} LayerPosition;

typedef struct __attribute__((packed)) {
    u32 graphics_offset;
    u32 palette_offset;
    u32 layers_offset;
    u8 count;
    u8 variable_counts;
    u8 indices[10];
    LayerPosition positions[0];
} LayerData;

typedef struct {
    u16 selected;
    u8 unknown_02[0x26];
    u8 entry;
    u8 layer;
} ResourceSelection;

typedef struct {
    u8 active;
    u8 mode;
    u8 phase;
    u8 unknown_03;
    const u32 *graphics;
    const u32 *palettes;
    const u32 *layers;
    void *secondary_destination;
    void *primary_destination;
    s16 tile_x;
    s16 tile_y;
    u8 unknown_1C[4];
    u8 first;
    u8 last;
    u16 index;
    u16 x, y;
} LayerRequest;

typedef struct {
    u8 unknown_00[0x168];
    void *pending_resource;
    void *pending_stream;
    u8 unknown_170[0x14];
    LayerRequest request;
} ResourceState;

extern ResourceState g_state_02007F40;
extern ResourceSelection data_02007F10;
extern const u8 data_08569104[];
extern u16 func_080035A8(u8 layer);
extern u8 func_0801E648(void);

static inline u8 transfer_idle(void)
{
    return g_state_02007F40.pending_resource == 0;
}

static inline u32 stream_idle(void)
{
    u32 idle = 0;
    if (g_state_02007F40.pending_stream == 0)
        idle = 1;
    return idle;
}

/* Complete 0x080200C8..0x08020274, 428 bytes. */
u8 func_080200C8(u16 index, void *secondary_destination, void *primary_destination)
{
    LayerRequest *request = &g_state_02007F40.request;
    const u8 *base = data_08569104;
    ResourceSelection *selection;
    const ResourceRecord *record = &((const ResourceRecord *)base)[data_02007F10.selected];
    const LayerData *data = (const LayerData *)(base + record->layer_data_offset);
    const u32 *graphics, *palettes, *layers;

    if (!transfer_idle() || !stream_idle())
        return 0;
    graphics = (const u32 *)((const u8 *)data + data->graphics_offset);
    palettes = (const u32 *)((const u8 *)data + data->palette_offset);
    layers = (const u32 *)((const u8 *)data + data->layers_offset);
    if (!data->variable_counts) {
        request->first = data_02007F10.layer;
        request->last = data_02007F10.layer;
    } else {
        u8 first = data->indices[data_02007F10.layer];
        u8 end = data->indices[data_02007F10.layer + 1];
        first -= data->indices[0];
        end -= data->indices[0];
        request->first = first;
        request->last = end - 1;
    }
    selection = &data_02007F10;
    request->x = data->positions[selection->layer].x;
    request->y = data->positions[selection->layer].y;
    request->active = 1;
    request->mode = 0;
    request->phase = selection->layer;
    request->graphics = graphics;
    request->palettes = palettes;
    request->layers = layers;
    request->secondary_destination = secondary_destination;
    request->primary_destination = primary_destination;
    request->index = index;
    g_control_flags_03000940.display &= ~func_080035A8(3);
    if (func_0801E648())
        g_control_flags_03000940.display &= ~func_080035A8(2);
    selection->layer++;
    selection->entry = data->indices[selection->layer];
    return 1;
}
