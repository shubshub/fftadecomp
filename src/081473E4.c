#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry;

typedef struct PaletteTransition PaletteTransition;

extern u16 data_03003860[];
extern PaletteEntry data_03003E68[];
extern u16 func_08148384(u16 color, u16 red, u16 green, u16 blue);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* 0x081473E4..0x081474BC - 216 bytes including literal pool. */
PaletteTransition *func_081473E4(u16 start, u16 count, u16 duration,
                                u16 red, u16 green, u16 blue)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++) {
        u16 source_red = data_03003860[index] & 0x1F;
        u16 source_green = (data_03003860[index] & 0x3E0) >> 5;
        u16 source_blue = (data_03003860[index] & 0x7C00) >> 10;

        source_red = source_red > 2 ? source_red : 3;
        source_green = source_green > 2 ? source_green : 3;
        source_blue = source_blue > 2 ? source_blue : 3;

        data_03003860[index] = source_red | (source_green << 5) | (source_blue << 10);
        data_03003E68[index].color = func_08148384(data_03003860[index], red, green, blue);
    }

    return func_08146E54(start, end, duration, 0);
}
