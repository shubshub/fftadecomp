#include "ffta.h"

// Complete [0x0806FABC, 0x0806FB50): 148 bytes, 64 reachable instructions.
typedef struct {
    u16 name;
    u8 unknown_02[6];
    u8 kind;
    u8 unknown_09[0x17];
} Record0806FABC;

typedef struct {
    u16 id;
    u16 kind;
    u8 sources[4];
} GrantedAbility;

typedef struct {
    u16 count;
    u16 unknown_02;
    GrantedAbility entries[3];
} GrantedAbilities;

typedef struct {
    u8 unknown_00[0x1A];
    u8 width;
    u8 unknown_1B[0x35];
    u16 first_tile;
} Menu0806FABC;

extern const Record0806FABC g_table_0851D180[];
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];
extern void func_0806FFAC(Menu0806FABC *menu, const u8 *source, u16 index);
extern u8 func_080C8D14(u16 id, GrantedAbilities *list);

void func_0806FABC(Menu0806FABC *menu, u16 id)
{
    GrantedAbilities list;
    u8 width = menu->width;
    u8 count;
    u8 i;

    func_0806FFAC(menu, g_table_08526680[g_table_0851D180[id].name], menu->first_tile);
    if (g_table_0851D180[id].kind == 0x1B)
        return;
    count = func_080C8D14(id, &list);
    for (i = 0; i < count; i++)
        func_0806FFAC(menu, g_table_085567F0[list.entries[i].id],
                      menu->first_tile + (i + 1) * (width << 1));
}
