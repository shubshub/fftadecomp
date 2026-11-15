#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry;

typedef struct PaletteTransition PaletteTransition;

extern PaletteEntry data_03003E68[];
extern u16 func_08148384(u16 color, u16 red, u16 green, u16 blue);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* 0x081474BC..0x081475A4 - 232 bytes including literal pool. */
PaletteTransition *func_081474BC(u16 start, u16 count, u16 duration, const u16 *colors,
                                u16 red, u16 green, u16 blue)
{
    u16 end = start + count - 1;
    u16 index;
    u16 source;

    if (end > 511)
        end = 511;

    for (index = start, source = 0; index <= end; index++, source++) {
        u16 source_red = colors[source] & 0x1F;
        u16 source_green = (colors[source] & 0x3E0) >> 5;
        u16 source_blue = (colors[source] & 0x7C00) >> 10;

        source_red = source_red > 2 ? source_red : 3;
        source_green = source_green > 2 ? source_green : 3;
        source_blue = source_blue > 2 ? source_blue : 3;

        data_03003E68[index].color = func_08148384(
            source_red | (source_green << 5) | (source_blue << 10), red, green, blue);
    }

    return func_08146E54(start, end, duration, 0);
}
