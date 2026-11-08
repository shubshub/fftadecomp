#include "ffta.h"

/* func_08037C84: 0x08037C84-0x08037DF0 (364 bytes incl. literal pool) */

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2A[0x22];
} Renderer;

typedef struct {
    u8 unknown_00[8];
    u8 kind;
    u8 enabled : 1;
} TransferResource;

typedef struct {
    u8 unknown_00[0x0C];
    u8 first_width;
    u8 first_height;
    u8 unknown_0E[2];
    u16 *first_destination;
    u16 *first_source;
    u8 unknown_18[0x0C];
    u8 second_width;
    u8 second_height;
    u8 unknown_26[2];
    u16 *second_destination;
    u16 *second_source;
    u16 renderer;
    u8 mode;
    u8 unknown_33[5];
    u16 field_38;
    u8 unknown_3A[4];
    u16 field_3E;
    u8 unknown_40[8];
    TransferResource *resource;
    u8 unknown_4C[0x80];
} TransferSlot;

typedef struct {
    u8 unknown_0000[0x954];
    TransferSlot slots[1];
} TransferState;

extern TransferState *g_state_03002810;
extern Renderer data_030009E0[];
extern u16 data_06008000[];

void func_08037C84(u32 slot, TransferResource *resource, u32 renderer, u32 column,
                   u32 row, u8 mode, u32 kind, u32 enabled)
{
    g_state_03002810->slots[slot].first_width = data_030009E0[renderer].width;
    g_state_03002810->slots[slot].first_height = data_030009E0[renderer].height;
    g_state_03002810->slots[slot].first_destination = data_06008000;
    g_state_03002810->slots[slot].first_source =
        data_030009E0[renderer].second_plane + data_030009E0[renderer].width * row + column;
    g_state_03002810->slots[slot].second_width = data_030009E0[renderer].width;
    g_state_03002810->slots[slot].second_height = data_030009E0[renderer].height;
    g_state_03002810->slots[slot].second_destination = data_06008000;
    g_state_03002810->slots[slot].second_source =
        data_030009E0[renderer].first_plane + data_030009E0[renderer].width * row + column;
    g_state_03002810->slots[slot].renderer = renderer;
    g_state_03002810->slots[slot].field_38 = 0;
    g_state_03002810->slots[slot].field_3E = 0;
    g_state_03002810->slots[slot].mode = mode;
    g_state_03002810->slots[slot].resource = resource;
    g_state_03002810->slots[slot].resource->kind = kind;
    g_state_03002810->slots[slot].resource->enabled = enabled;
}
