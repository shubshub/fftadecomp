#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry;

typedef struct PaletteTransition PaletteTransition;

extern u16 data_03003860[];
extern PaletteEntry data_03003E68[];
extern u16 func_081478DC(u16 color, u8 amount);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* 0x08147EC8..0x08147F50 - 136 bytes, 59 instructions including literal pool. */
PaletteTransition *func_08147EC8(u16 start, u16 count, u16 duration, u8 amount)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = func_081478DC(data_03003860[index], amount);

    return func_08146E54(start, end, duration, 0);
}
