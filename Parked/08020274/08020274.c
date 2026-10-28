#include "ffta.h"

typedef struct __attribute__((packed)) {
    u8 unknown_00[0x50];
    u32 layer_data_offset;
    u32 unknown_54;
} ResourceRecord;

typedef struct __attribute__((packed)) {
    u32 graphics_offset;
    u32 palette_offset;
    u32 layers_offset;
    u8 unknown_0C;
    u8 variable_counts;
    u8 indices[0];
} LayerData;

typedef struct {
    u16 resource_index;
    u8 unknown_02[0x26];
    u8 entry;
    u8 layer;
} ResourceState;

typedef struct {
    u8 unknown_00[0x168];
    void *pending_resource;
    u32 unknown_16C;
    u32 configuration;
    u8 unknown_174[0xC];
    u8 mode;
} MapState;

extern const ResourceRecord data_08569104[];
extern ResourceState data_02007F10;
extern MapState g_state_02007F40;
extern void *data_020080AC;
extern u8 data_02003CB0[];

void func_0801F548(const void *data, u32 index);
void func_0801F62C(const void *data, u32 index);
void *func_0801ED24(void *resource, u32 configuration, u8 mode,
                   u32 x, u32 y, u32 flags, u32 unknown, u32 buffer_size);
void func_0801EFB0(void);
void func_08141890(const void *source, void *destination);
void func_0801F098(const void *source, const void *boundary);

static inline u8 resource_finished(void)
{
    return g_state_02007F40.pending_resource == 0;
}

static inline int transfer_finished(void)
{
    return data_020080AC == 0;
}

static inline void apply_layer(const u32 *layers, u16 layer_index)
{
    const u32 *cursor;
    const u32 *last;
    u32 last_offset;
    const void *boundary;
    const u8 *source;

    cursor = layers;
    while (*cursor == 0) {
        cursor++;
    }
    last_offset = (*cursor - 4) & 0x3FFFC;
    boundary = 0;
    last = (const u32 *)((const u8 *)layers + last_offset);
    if (*last != 0xFFFFFFFF) {
        boundary = (const u8 *)layers + *last;
    }
    if (layers[layer_index] != 0) {
        source = (const u8 *)layers + layers[layer_index];
        if (*source != 0) {
            func_08141890(source, data_02003CB0);
            source = data_02003CB0;
        } else {
            source += 4;
        }
        func_0801F098(source, boundary);
    }
}

/* Complete target: [0x08020274, 0x0802046A), 502 bytes. */
void func_08020274(u8 count)
{
    const u8 *resource_base = (const u8 *)data_08569104;
    const ResourceRecord *record = &data_08569104[data_02007F10.resource_index];
    const LayerData *data = (const LayerData *)(resource_base + record->layer_data_offset);
    const u8 *graphics;
    const u8 *palettes;
    const u32 *layers;
    u8 layer;

    data_02007F10.layer = count;
    data_02007F10.entry = data->indices[data_02007F10.layer];
    graphics = (const u8 *)data + data->graphics_offset;
    palettes = (const u8 *)data + data->palette_offset;
    layers = (const u32 *)((const u8 *)data + data->layers_offset);

    for (layer = 0; layer < count; layer++) {
        u8 entries = 1;
        u8 first;
        u8 entry;

        if (data->variable_counts != 0) {
            u8 start = data->indices[layer];
            u8 end = data->indices[layer + 1];
            entries = end - start;
        }
        first = data->indices[layer] - data->indices[0];
        for (entry = 0; entry < entries; entry++) {
            func_0801F548(graphics, first + entry);
            while (resource_finished() == 0) {
                g_state_02007F40.pending_resource =
                    func_0801ED24(g_state_02007F40.pending_resource,
                                  g_state_02007F40.configuration,
                                  g_state_02007F40.mode,
                                  0, 0, 0, 0, 0x800);
            }
        }

        func_0801F62C(palettes, layer);
        while (transfer_finished() == 0) {
            func_0801EFB0();
        }

        apply_layer(layers, layer);
    }
}
