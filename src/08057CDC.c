#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 width;
    u8 unknown_16[6];
    u16 tile_base;
} MenuList;

typedef struct {
    const u8 *name;
    u8 unknown_04[3];
    u8 graphic;
    u8 unknown_08[0x20];
    u16 flags;
    u8 unknown_2A[0xDE];
} MenuUnit;

typedef struct {
    u8 unknown_00[0x80];
    MenuUnit units[24];
} Roster;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics;

extern Roster g_state_02000000;
extern Graphics data_030008B0;
extern u8 func_0805871C(MenuList *list, u8 row);
extern void func_08013A88(void *destination, u16 count);
extern u16 func_08015110(void *context, void *destination, const u8 *name,
                         u8 style, u8 spacing);
extern void func_080CB9E0(void *destination, u32 graphic);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0x08057CDC, 0x08057E24), 328 bytes.
 * The original copies the buffer even when graphic 0 or 1 gives the decoder
 * an out-of-range archive index. A drawable unit supplies a graphic >= 2. */
void func_08057CDC(MenuList *list, void *text, u8 unit_id, u8 row, u8 mode)
{
    u32 buffer[64];
    u32 bank = func_0805871C(list, row);
    u32 bank_row = (bank & 3) * 5;
    u32 offset = bank_row * list->width;
    const u8 *name = g_state_02000000.units[unit_id].name;
    u8 graphic = g_state_02000000.units[unit_id].graphic;
    u16 flagged = g_state_02000000.units[unit_id].flags & 0x10;
    u8 *tiles;

    switch (mode) {
    case 0:
        tiles = data_030008B0.tiles + (list->tile_base + offset) * 32;
        func_08013A88(tiles, list->width * 2);
        if (flagged)
            func_08015110(text, tiles, name, 4, 1);
        else
            func_08015110(text, tiles, name, 0, 1);

        tiles = data_030008B0.tiles + (list->tile_base + offset + list->width * 2) * 32;
        func_08013A88(tiles, list->width * 2);
        func_080CB9E0(buffer, graphic);
        func_0814186C(buffer, tiles, 128);
        break;
    case 1:
        tiles = data_030008B0.tiles + (list->tile_base + offset) * 32;
        func_08013A88(tiles, list->width * 2);
        func_08015110(text, tiles, name, 0, 1);

        tiles = data_030008B0.tiles + (list->tile_base + offset + list->width * 2) * 32;
        func_08013A88(tiles, list->width * 2);
        func_080CB9E0(buffer, graphic);
        func_0814186C(buffer, tiles, 128);
        break;
    }
}
