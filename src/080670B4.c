#include "ffta.h"

/* Complete target: [0x080670B4, 0x080674B0), 1020 bytes. */
typedef struct { u16 id; u8 quantity; u8 reference_quantity; } Item;
typedef struct {
    u8 unknown_00[0x14];
    u8 text_context[0x410];
    Item *entries[0];
} ItemTable;
typedef struct {
    u8 unknown_00[0x6A];
    u16 first;
    u8 unknown_6C[0x15];
    u8 selection;
} Selection;
typedef struct { u8 unknown_00[2]; u8 width; u8 unknown_03[13]; } Layout;
typedef struct {
    u16 *destination;
    u8 unknown_04[0xC];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
} Renderer;
typedef struct {
    u8 unknown_00[0xC];
    u16 *tilemap;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[6];
    u16 first_tile;
    u8 unknown_1E[2];
} TileList;
typedef struct { u16 name; u16 count; u8 categories[4]; } AbilityGroup;
typedef union {
    struct { u16 count; u16 unknown_02; AbilityGroup groups[3]; } records;
    struct { u8 header[8]; u8 categories[20]; } columns;
} AbilityGroups;
typedef struct {
    ItemTable *table;
    Selection *selection;
    u8 unknown_08;
    u8 flags;
    u16 animation_timer;
    u8 frame_indices[3];
    u8 ability_count;
    u8 unknown_10[8];
    Layout layout;
    Renderer renderer;
    TileList list;
    u8 unknown_74[0x28];
    AbilityGroups abilities;
    Item *selected;
    u16 *tilemap;
} Menu;
typedef struct { u8 unknown_00[0x1D]; u8 effects; u8 unknown_1E[2]; } ItemRecord;
typedef struct { u8 category; u8 effect; } __attribute__((packed)) EffectPair;
typedef struct { u8 count; u8 unknown_01; EffectPair pairs[9]; } EffectList;
typedef struct { u8 unknown_00[6]; u8 category; u8 value; } Effect;
typedef struct { u8 unknown_00[0x10]; u8 *tiles; } Graphics;

extern Graphics data_030008B0;
extern u8 data_02003CB0[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern const ItemRecord g_table_0851D180[];
extern const EffectList g_table_08520080[];
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];
extern u16 func_08017B9C(TileList *, u32);
extern void func_08013A88(void *, u16);
extern u32 func_080CA7A4(u16, u8);
extern void func_08015110(void *, void *, const void *, u32, u32);
extern void func_0802AB64(TileList *, u16, u16, u8, u8, u16, u8);
extern u8 func_080C8D14(u16, AbilityGroups *);
extern u32 func_080C8570(u8, u8, u8);
extern const Effect *func_080CD480(u8, u8);
extern void func_0802ACA0(u16 *, u16, u8, u16);
extern void func_08029730(u16 *, u8, u16);
extern void func_0802AC14(Renderer *, u16 *, u8, u8, u8);
extern void func_080CB9E0(void *, u32);
extern void func_0814186C(const void *, void *, u32);
extern u32 func_080CBA14(u8);

static inline const ItemRecord *item_record(u16 id)
{
    return &g_table_0851D180[id];
}

static inline u8 *ability_categories(Menu *menu)
{
    return menu->abilities.columns.categories;
}

static inline void draw_ability_icons(Menu *menu)
{
    TileList *list = &menu->list;
    Renderer *renderer = &menu->renderer;
    s32 width = renderer->width;
    s32 i;
    u16 tile;
    u8 *category;
    u8 palette;
    void *buffer;
    s32 category_index;

    menu->animation_timer = 1;
    menu->ability_count = func_080C8D14(menu->selected->id, &menu->abilities);
    for (i = 0; i < menu->ability_count; i++) {
        tile = 0x251 + (i << 3);
        category_index = menu->frame_indices[i] + (i << 3);
        category = ability_categories(menu) + category_index;
        buffer = data_02003CB0;
        if (*category == 0xFF) {
            menu->ability_count = 0;
            break;
        }
        func_080CB9E0(buffer, *category);
        func_0814186C(buffer, data_030008B0.tiles + tile * 32, 0x80);
        palette = func_080CBA14(*category);
        func_0802AB64(list, width * 7 + 1 + (width << 2) * i,
                     tile, width, 4, palette, 0);
    }
    if (menu->ability_count)
        func_0802AC14(renderer, menu->tilemap, renderer->x,
                     renderer->y, renderer->height);
}

void func_080670B4(Menu *menu)
{
    TileList *list = &menu->list;
    Renderer *renderer = &menu->renderer;
    Layout *layout = &menu->layout;
    s32 width = renderer->width;
    u8 *tiles;
    Item *item;
    u8 count;
    const EffectList *effects;
    const Effect *effect;
    s32 first_tile;
    s32 i;
    u16 *category_label;
    u16 *effect_label;
    u16 selected_index;
    const u8 *text;

    g_callbacks_0836D4B8[0](menu->tilemap, 0x1D4);
    tiles = data_030008B0.tiles + func_08017B9C(list, 0) * 32;
    func_08013A88(tiles, list->width * 2);
    selected_index = menu->selection->first;
    selected_index += menu->selection->selection;
    item = menu->table->entries[selected_index];
    menu->selected = item;
    text = g_table_08526680[func_080CA7A4(item->id, 0)];
    func_08015110(menu->table->text_context, tiles, text, 5, 1);
    func_0802AB64(list, width + 1, list->first_tile, width, layout->width, 0, 1);
    count = func_080C8D14(item->id, &menu->abilities);
    effects = &g_table_08520080[item_record(item->id)->effects];
    first_tile = list->first_tile + width * 2;
    for (i = 0; i < 3; i++) {
        s32 j;
        tiles += width * 64;
        func_08013A88(tiles, list->width * 2);
        if (i < count && menu->abilities.records.groups[i].categories[0] != 0xFF) {
            text = g_table_085567F0[menu->abilities.records.groups[i].name];
            func_08015110(menu->table->text_context, tiles, text, 5, 1);
            func_0802AB64(list, width * 5 + 1 + (width << 2) * i,
                         first_tile + width * i * 2, width, layout->width, 0, 1);
            for (j = 0; j < effects->count; j++) {
                if (menu->abilities.records.groups[i].categories[0] == effects->pairs[j].category) {
                    u16 *row;
                    u16 value;
                    effect = func_080CD480(
                        func_080C8570(effects->pairs[j].category,
                                     effects->pairs[j].category, 1), effects->pairs[j].effect);
                    row = menu->tilemap + width * (i * 4 + 8);
                    category_label = row + 6;
                    func_0802ACA0(category_label, 0x24F, 15, 2);
                    value = effect->value * 10;
                    if (value > 999)
                        value = 999;
                    func_08029730(row + 8, 3, value);
                    break;
                }
            }
        }
    }
    category_label = menu->tilemap + width * 3 + 7;
    g_callbacks_0836D4B8[0](category_label, 6);
    effect_label = category_label + width;
    g_callbacks_0836D4B8[0](effect_label, 10);
    if (count) {
        effect = func_080CD480(
            func_080C8570(effects->pairs[0].category,
                         effects->pairs[0].category, 1), effects->pairs[0].effect);
        switch (effect->category) {
        case 2:
            func_0802ACA0(category_label, 0x238, 13, 2);
            func_0802ACA0(effect_label, 0x23A, 13, 5);
            break;
        case 3:
            func_0802ACA0(category_label, 0x23F, 13, 3);
            func_0802ACA0(effect_label, 0x242, 13, 5);
            break;
        case 5:
            func_0802ACA0(category_label, 0x247, 13, 3);
            func_0802ACA0(effect_label, 0x24A, 13, 5);
            break;
        case 1:
            func_0802ACA0(category_label, 0x230, 13, 3);
            func_0802ACA0(effect_label, 0x233, 13, 5);
            break;
        }
    }
    func_0802AC14(renderer, menu->tilemap, renderer->x, renderer->y, renderer->height);
    menu->animation_timer = 0;
    menu->frame_indices[2] = 0;
    menu->frame_indices[1] = 0;
    menu->frame_indices[0] = 0;
    if (!(menu->flags & 8))
        draw_ability_icons(menu);
}
