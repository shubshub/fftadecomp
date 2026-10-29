#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry08147B28;

typedef struct PaletteTransition PaletteTransition;

extern u16 data_03003860[];
extern PaletteEntry08147B28 data_03003E68[];
extern u16 func_081477DC(u16 color);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* Target: complete [0x08147B28, 0x08147BA4), 124 bytes, 53 instructions. */
PaletteTransition *func_08147B28(u16 start, u16 count, u16 duration)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = func_081477DC(data_03003860[index]);

    return func_08146E54(start, end, duration, 0);
}
