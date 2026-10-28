#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[6];
    u16 tileBase;
    u8 unknown_1E;
    u8 palette;
} MenuWindow;

typedef struct {
    u8 unknown_00[0x108];
} MenuUnitRecord;

extern MenuUnitRecord g_state_02000000[];
extern u8 func_0805871C(MenuWindow *window, u8 row);
extern u8 func_080CBA14(u8 value);
extern void func_0802AB64(MenuWindow *window, u16 destination, u16 source,
                         u8 width, u8 height, u8 palette, u8 copy);
extern void func_0802ACA0(u16 *destination, u16 tile, u8 palette, u8 count);
extern void func_08029730(u16 *destination, u32 digits, u8 value);

/* Complete target: [0x08057E98, 0x08058104), 620 bytes, 290 instructions. */
void func_08057E98(MenuWindow *window, u8 row, u8 unitId, u8 mode)
{
    u8 bank = func_0805871C(window, row);
    u8 width = window->width;
    u16 rowStart = row * 5;
    u16 base = rowStart * width;
    u32 bankRow = (bank & 3) * 5;
    u16 source = bankRow * width + window->tileBase;
    u8 *unit;
    u8 palette;
    u16 destination;
    u16 i;

    unit = (u8 *)&g_state_02000000[unitId];
    palette = func_080CBA14(unit[0x87]);

    switch (mode)
    {
    case 0:
    {
        destination = base;
        func_0802AB64(window, destination, source, window->width,
                     window->width, window->palette, 1);
        destination += 2 * window->width;
        source += 2 * window->width;
        func_0802AB64(window, destination, source, window->width, 4, palette, 0);
        func_0802ACA0(&window->tiles[base + 2 * window->width + 4], 0x93, 14, 6);
        func_0802ACA0(&window->tiles[base + 3 * window->width + 4], 0x99, 14, 6);
        func_08029730(&window->tiles[base + 3 * window->width + 10], 2, unit[0x170]);
        func_0802ACA0(&window->tiles[base + 3 * window->width + 12], 0x8F, 14, 4);
        destination = base + 4 * window->width;
        for (i = 0; i < window->width; i++, destination++)
            window->tiles[destination] = 0;
        break;
    }
    case 1:
    {
        destination = base;
        func_0802AB64(window, destination, source, window->width,
                     window->width, window->palette, 1);
        destination += 2 * window->width;
        source += 2 * window->width;
        func_0802AB64(window, destination, source, window->width, 4, palette, 0);
        func_0802ACA0(&window->tiles[base + 2 * window->width + 5], 0x120, 15, 2);
        func_0802ACA0(&window->tiles[base + 3 * window->width + 5], 0x122, 15, 2);
        func_0802ACA0(&window->tiles[base + 2 * window->width + 9], 0x120, 14, 2);
        func_0802ACA0(&window->tiles[base + 3 * window->width + 9], 0x122, 14, 2);
        func_08029730(&window->tiles[base + 3 * window->width + 7], 1, unit[0x183]);
        func_08029730(&window->tiles[base + 3 * window->width + 11], 1, unit[0x182]);
        destination = base + 4 * window->width;
        for (i = 0; i < window->width; i++, destination++)
            window->tiles[destination] = 0;
        break;
    }
    }
}
