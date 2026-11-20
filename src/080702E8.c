#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u8 stride;
    u8 unknown_0D[7];
    u16 *tiles;
} TileMap;

typedef struct {
    u8 unknown_00[0x39F4];
    u8 text_context[1];
} MenuState;

typedef struct {
    u16 name;
    u8 unknown_02[0x1E];
} ItemRecord;

extern MenuState *data_0200F428;
extern const ItemRecord g_table_0851D180[];
extern const u8 *const g_table_08526680[];

extern void func_08013A88(void *destination, u16 count);
extern void func_080CB980(void *destination, u32 id);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u16 func_08015110(void *context, void *destination, const u8 *text,
                         u8 style, u8 spacing);
extern u8 func_080CB99C(u16 id);

/* Complete target [0x080702E8, 0x08070414), 300 bytes.
 * Both callers pass the current menu item. This row expects a valid item ID. */
void func_080702E8(TileMap *map, u8 *graphics, u16 id, u8 x, u8 y)
{
    u32 icon[32];
    u16 offset;
    u16 first_tile;
    u16 i;

    func_08013A88(graphics, 26);
    func_080CB980(icon, id);
    func_0814186C(icon, graphics, 0x40);
    func_08015110(data_0200F428->text_context, graphics + sizeof(icon),
                  g_table_08526680[g_table_0851D180[id].name], 0, 1);

    offset = y * map->stride + x;
    first_tile = ((u32)graphics - 0x06008000) >> 5;
    for (i = 0; i < 2; i++) {
        map->tiles[offset + i] = (first_tile + i) | ((func_080CB99C(id) + 13) << 12);
        map->tiles[offset + i + map->stride] = (first_tile + (i + 2)) | ((func_080CB99C(id) + 13) << 12);
    }
    for (i = 2; i < 13; i++) {
        map->tiles[offset + i] = (first_tile + i * 2) | 0xC000;
        map->tiles[offset + i + map->stride] = (first_tile + i * 2 + 1) | 0xC000;
    }
}
