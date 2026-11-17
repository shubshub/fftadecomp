#include "ffta.h"

// Complete [0x0806FABC, 0x0806FB50): 148 bytes, 74 instructions.
typedef struct {
    u16 name;
    u8 unknown_02[6];
    u8 kind;
    u8 unknown_09[0x17];
} Record0806FABC;

typedef struct {
    u16 name;
    u8 unknown_02[6];
} Entry0806FABC;

typedef struct {
    u8 unknown_00[4];
    Entry0806FABC entries[3];
} List0806FABC;

typedef struct {
    u8 unknown_00[0x1A];
    u8 spacing;
    u8 unknown_1B[0x35];
    u16 tile;
} Menu0806FABC;

extern const Record0806FABC g_table_0851D180[];
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];
extern void func_0806FFAC(Menu0806FABC *menu, const u8 *source, u16 index);
extern u8 func_080C8D14(u16 id, List0806FABC *list);

void func_0806FABC(Menu0806FABC *menu, u16 id)
{
    List0806FABC list;
    u8 spacing = menu->spacing;
    u8 count;
    u8 i;

    func_0806FFAC(menu, g_table_08526680[g_table_0851D180[id].name], menu->tile);
    if (g_table_0851D180[id].kind == 0x1B)
        return;
    count = func_080C8D14(id, &list);
    for (i = 0; i < count; i++)
        func_0806FFAC(menu, g_table_085567F0[list.entries[i].name],
                      menu->tile + (i + 1) * (spacing << 1));
}
