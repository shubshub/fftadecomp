#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry;

extern PaletteEntry data_03003E68[];
typedef struct PaletteTransition PaletteTransition;
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* 0x08147CC0..0x08147D2C - 108 bytes including literal pool. */
PaletteTransition *func_08147CC0(u16 start, u16 count, u16 duration,
                                u16 red, u16 green, u16 blue)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = (green << 5) | red | (blue << 10);

    return func_08146E54(start, end, duration, 0);
}
