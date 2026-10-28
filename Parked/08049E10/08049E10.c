#include "ffta.h"

/* 0x08049E10..0x08049ECE: 190 bytes. */
typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0A : 6;
} MenuResource;

typedef struct {
    u8 unknown_00[0x24];
    MenuResource *slots[16];
} MenuResources;

typedef struct {
    u32 unknown_00;
    MenuResources *resources;
} MenuContext;

typedef struct {
    u16 index;
    u16 type;
    u16 slot;
    u16 unknown_06;
    const char *name;
    u16 field_0C;
    u8 unknown_0E[6];
} ResourceMenuRow;

typedef struct {
    s32 count;
    const void *format;
    u8 unknown_08[4];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 field_10;
    u8 field_12;
    u8 unknown_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    ResourceMenuRow *rows;
    u8 unknown_1C[0x214];
    ResourceMenuRow storage[16];
} ResourceMenu;

extern MenuContext *g_state_03002810;
extern const u8 g_table_08526680[];
extern const char * const g_table_0855A64C[];

s32 func_08049E10(ResourceMenu *menu)
{
    s32 count;
    s32 i;
    ResourceMenuRow *row;
    MenuContext *context;
    s32 height;
    const u8 *format;

    menu->rows = menu->storage;
    count = 0;
    i = 0;
    format = g_table_08526680;
    context = g_state_03002810;
    row = menu->storage;
    for (; i < 16; i++) {
        MenuResource *resource = context->resources->slots[i];

        if (resource->id != 0 && resource != 0) {
            row->index = count;
            row->type = 1;
            row->slot = i;
            row->name = g_table_0855A64C[resource->id];
            row->field_0C = 0;
            row++;
            count++;
        }
    }
    if (count > 6)
        height = 15;
    else
        height = count * 2 + 3;
    menu->format = format;
    menu->x = 0;
    menu->y = 0;
    menu->width = 14;
    menu->height = height;
    menu->field_10 = 203;
    menu->field_12 = 0;
    menu->field_14 = 0;
    menu->field_16 = 16;
    menu->field_17 = 0;
    menu->count = count;
    return count;
}
