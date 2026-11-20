#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x68C];
    u8 text[0xC38 - 0x68C];
    u8 enabled;
    u8 ticks;
    u8 counts[3];
    u8 current[3];
    u8 frames[3][3];
    u8 *destinations[3];
    u16 item;
} InventoryPanel;

typedef struct {
    u16 name;
    u16 description;
    u8 unknown_04[4];
    u8 category;
    u8 unknown_09[0x14];
    u8 grants;
    u8 unknown_1E[2];
} ItemDefinition;

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

typedef u8 ItemAbility[2];
typedef struct {
    u8 count;
    u8 unknown_01;
    ItemAbility entries[9];
} ItemAbilities;

typedef struct { u8 *rows[3]; } TileRows;

extern InventoryPanel *data_03002818;
extern u8 data_02003CB0[];
extern u8 data_0600E1A0[];
extern const TileRows data_081499C4;
extern const TileRows data_081499D0;
extern const ItemDefinition g_table_0851D180[];
extern const ItemAbilities g_table_08520080[];
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u16 func_08015110(void *state, void *destination, const u8 *text, u8 style, u8 reset);
extern u8 func_080C8D14(u16 item, GrantedAbilities *out);
extern void func_080CB9E0(void *destination, u32 graphic);
extern u32 func_080CBA14(u8 index);
extern void func_0808B80C(s32 surface, u16 *tiles, u16 tile, u16 width, u16 flags);
extern u32 func_080C8570(u8 first, u8 second, u8 selector);
extern const u8 *func_080CD480(u8 first, u8 second);
extern void func_08035678(u16 tile, u16 *destination, u32 count, u16 step);
extern void func_08035A68(u16 *dst, u16 count, u32 value, u16 base);
extern void func_0808C53C(s32 mode);
extern void func_0808A604(u32 object, u32 animation);

#define CLEAR_TILES(dest, halfwords) do { \
    u16 zero = 0; \
    func_0814186C(&zero, dest, 0x01000000 | (halfwords)); \
} while (0)

/* Original [0x0808C630, 0x0808C9C4), 916 bytes, 367 reachable instructions.
 * Draws item and ability names, animated job icons and ability-point costs. */
void func_0808C630(u32 item)
{
    GrantedAbilities list;
    TileRows names = data_081499C4;
    TileRows icons = data_081499D0;
    u8 i, j, k, count, used;
    u8 palette;
    const ItemAbilities *abilities;
    const u8 *ability;
    u32 cost;

    data_03002818->enabled = 1;
    data_03002818->ticks = 60;
    data_03002818->item = item;
    CLEAR_TILES(data_0600E1A0, 0x580);
    for (i = 0; i < 3; i++) {
        CLEAR_TILES(func_0808B8E4(6, 1, 6, i * 4 + 8), 6);
        data_03002818->frames[0][i] = 0;
        data_03002818->frames[1][i] = 0;
        data_03002818->frames[2][i] = 0;
        data_03002818->current[i] = 0;
        data_03002818->counts[i] = 0;
    }
    {
        u16 tail_fill;
        const u8 *name = g_table_08526680[g_table_0851D180[item].name];
        u8 *dest = data_0600E1A0;
        func_08015110(data_03002818->text, dest, name, 1, 1);
        if (g_table_0851D180[item].category != 27) {
            count = func_080C8D14(item, &list);
            for (i = 0; i < count; i++) {
                name = g_table_085567F0[list.entries[i].id];
                func_08015110(data_03002818->text, names.rows[i], name, 1, 1);
                for (used = j = 0; j < list.entries[i].kind; j++) {
                    data_03002818->frames[i][j] = list.entries[i].sources[j];
                    if (list.entries[i].sources[j] != 0)
                        used++;
                }
                if (used > 1)
                    data_03002818->counts[i] = used;
                data_03002818->destinations[i] = icons.rows[i];
                func_080CB9E0(data_02003CB0, list.entries[i].sources[0]);
                func_0814186C(data_02003CB0, icons.rows[i], 0x80);
                palette = func_080CBA14(list.entries[i].sources[0]);
                func_0808B80C(6, func_0808B8E4(6, 1, 1, i * 4 + 7),
                              0x365 + i * 8, 4, palette << 12);
                abilities = &g_table_08520080[g_table_0851D180[item].grants];
                for (k = 0; k < abilities->count; k++) {
                    if (list.entries[i].sources[0] == abilities->entries[k][0]) {
                        ability = func_080CD480(func_080C8570(abilities->entries[k][0],
                                                           abilities->entries[k][0], 1),
                                                abilities->entries[k][1]);
                        func_08035678(0xf14c, func_0808B8E4(6, 1, 6, i * 4 + 8), 2, 1);
                        cost = ability[7] * 10;
                        if (cost > 999)
                            cost = 999;
                        func_08035A68(func_0808B8E4(6, 1, 8, i * 4 + 8), 4, cost, 0xf000);
                        func_0808C53C(ability[6]);
                        break;
                    }
                }
            }
            if (count == 0) {
                tail_fill = 0;
                func_0814186C(&tail_fill, (void *)0x0600ECA0, 0x01000000 | 0x220);
            } else if (count == 1) {
                tail_fill = 0;
                func_0814186C(&tail_fill, (void *)0x0600EDA0, 0x01000000 | 0x100);
            } else if (count == 2) {
                tail_fill = 0;
                func_0814186C(&tail_fill, (void *)0x0600EEA0, 0x01000000 | 0x80);
            }
        } else {
            u16 second_fill;
            u16 *fill = &tail_fill;
            u16 zero = 0;
            *fill = zero;
            func_0814186C(fill, (void *)0x0600EFA0, 0x01000000 | 0xA0);
            second_fill = zero;
            func_0814186C(&second_fill, (void *)0x0600ECA0, 0x01000220);
        }
    }
    func_0808A604(6, 2);
}
