#include "ffta.h"

/* 0x080270CC..0x08027208: 316 bytes, 142 instructions. */
typedef struct {
    u32 unknown_00;
    u16 id;
    u8 kind;
    u8 unknown_07;
} AbilityEntry;

typedef struct {
    AbilityEntry *entries;
    u8 first;
    u8 last;
    u8 unknown_06;
    u8 maximum;
    u8 severity;
    u8 count;
} AbilityList;

typedef struct {
    u8 unknown_00[0xD];
    u8 mode;
    u8 unknown_0E[6];
    s32 *indices;
    u8 *enabled;
} AbilityListState;

typedef struct {
    u8 unknown_00[0x80];
    AbilityListState list;
} AbilityMenu;

typedef struct {
    u16 text;
    u8 unknown_02[2];
    u8 cost_type;
    u8 unknown_05[23];
} AbilityInfo;

typedef struct {
    u8 unknown_00[0x1C];
    u16 points;
} AbilityUser;

typedef struct {
    u8 unknown_00[0x18];
    AbilityUser *user;
} AbilityContext;

extern const AbilityInfo data_0855187C[];
extern AbilityContext *data_0200F438;
extern const void *g_table_085567F0[];
extern s32 func_080CCD50(u16 id, s32 category);
extern u8 func_080CDB3C(AbilityUser *user);
extern u8 func_080258C4(AbilityUser *user, u8 type);
extern u8 func_080161BC(const void *text);

void func_080270CC(AbilityMenu *menu, AbilityList *list)
{
    AbilityListState *state = &menu->list;
    s32 index;
    s32 count;

    list->severity = 0;
    index = list->first;
    count = 0;
    for (; index <= list->last; index++) {
        AbilityEntry *entry = &list->entries[index];

        if ((entry->kind == 1 || entry->kind == 4) && func_080CCD50(entry->id, 30)) {
            const AbilityInfo *info = &data_0855187C[entry->id];

            menu->list.indices[count] = index;
            if (func_080CDB3C(data_0200F438->user) && !func_080CCD50(entry->id, 20)) {
                if (info->cost_type) {
                    u32 cost = func_080258C4(data_0200F438->user, info->cost_type);

                    if (list->severity <= 2) {
                        list->severity = 3;
                    }
                    if (cost > 99) {
                        list->severity = 4;
                    }
                }
                menu->list.enabled[count] = 0;
            } else if (info->cost_type) {
                u32 cost = func_080258C4(data_0200F438->user, info->cost_type);

                if (list->severity <= 2) {
                    list->severity = 3;
                }
                if (cost > 99) {
                    list->severity = 4;
                }
                if (data_0200F438->user->points < cost) {
                    menu->list.enabled[count] = 0;
                }
            }
            count++;
            {
                u8 length = func_080161BC(g_table_085567F0[info->text]);

                if (length > list->maximum) {
                    list->maximum = length;
                }
            }
        }
    }
    if (list->severity) {
        state->mode = 9;
    }
    list->count = count;
}
