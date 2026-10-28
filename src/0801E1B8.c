#include "ffta.h"

typedef struct {
    u8 first_layer;
    u8 second_layer;
    u8 first_mode;
    u8 second_mode;
    u8 format;
    u8 unknown_05[0x0b];
    const void *resource;
    u16 *first_tilemap;
    u16 *second_tilemap;
    u8 unknown_1c[8];
    u16 target_x;
    u16 target_y;
    u16 shift_x;
    u16 shift_y;
} ScrollState0801E1B8;

typedef struct {
    u8 layer;
    u8 format;
    u8 mode;
    u8 unknown_03;
    u16 x;
    u16 y;
    const void *resource;
    u16 *tilemap;
} ScrollDescriptor0801E1B8;

extern ScrollState0801E1B8 g_state_02007F40;

void func_0801E1B8(u8 layer, ScrollDescriptor0801E1B8 *output)
{
    if (layer == 0) {
        output->layer = g_state_02007F40.first_layer;
        output->mode = g_state_02007F40.first_mode;
        output->tilemap = g_state_02007F40.first_tilemap;
    } else {
        output->layer = g_state_02007F40.second_layer;
        output->mode = g_state_02007F40.second_mode;
        output->tilemap = g_state_02007F40.second_tilemap;
    }
    output->format = g_state_02007F40.format;
    output->resource = g_state_02007F40.resource;
    output->x = g_state_02007F40.target_x - g_state_02007F40.shift_x;
    output->y = g_state_02007F40.target_y - g_state_02007F40.shift_y;
}
