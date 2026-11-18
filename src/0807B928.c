#include "ffta.h"

typedef struct {
    u16 name;
    u16 description;
    u16 unknown_04;
    u8 type;
    u8 required_points;
} Ability;

typedef struct {
    u8 unknown_00[6];
    u8 race;
    u8 unknown_07[0x40 - 7];
    u8 ability_points[0x8E];
    u8 unknown_CE[0x108 - 0xCE];
} Unit;

typedef struct {
    u8 unknown_00[0x1D0C];
    Unit *unit;
} State;

typedef struct {
    u16 position;
    u16 flags;
    u32 unknown_04;
    u32 name;
    u16 description;
    u8 points;
    u8 required_points;
    u8 type;
    u8 unknown_11[3];
} AbilityRow;

typedef struct {
    s32 count;
    const u8 *const *strings;
    u32 unknown_08;
    u8 x, y, width, height;
    u16 tile;
    u8 style;
    u8 unknown_13;
    u16 first_row;
    u8 row_height;
    u8 unknown_17;
    AbilityRow *rows;
    u8 unknown_1C[0x230 - 0x1C];
    AbilityRow entries[0x8E];
} AbilityList;

extern State *data_03002818;
extern const u8 *const g_table_085567F0[];
extern const u8 *func_080CCE60(Unit *unit, u8 mode, u8 *first, u8 *last);
extern const u8 *func_080CD480(u8 race, u8 ability);

s32 func_0807B928(u32 unused, u32 mode, AbilityList *list)
{
    /* The original writes each accepted byte index as a halfword at 0x0807B9BE. */
    u16 indices[256];
    u8 first, last;
    const Ability *abilities;
    s32 index, count;
    AbilityRow *rows;

    list->strings = g_table_085567F0;
    list->x = 0;
    list->y = 0;
    list->width = 20;
    list->height = 13;
    list->tile = 0x1A7;
    list->style = 0;
    list->first_row = 0;
    list->row_height = 16;
    list->unknown_17 = 0;
    rows = list->entries;
    list->rows = rows;
    abilities = (const Ability *)func_080CCE60(data_03002818->unit, mode, &first, &last);
    count = 0;
    rows[count].description = 0;
    for (index = first; index <= last; index++) {
        if (data_03002818->unit->ability_points[index] && abilities[index].type) {
            const Ability *ability;
            indices[count] = index;
            rows[count].position = count;
            rows[count].flags = 0;
            rows[count].name = abilities[index].name;
            rows[count].description = abilities[index].description;
            rows[count].points = data_03002818->unit->ability_points[index];
            ability = (const Ability *)func_080CD480(data_03002818->unit->race, index);
            rows[count].required_points = ability->required_points;
            rows[count].type = ability->type;
            count++;
        }
    }
    list->count = count;
    return count;
}
