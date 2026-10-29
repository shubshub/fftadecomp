#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry08147E28;

typedef struct PaletteTransition PaletteTransition;
extern PaletteEntry08147E28 data_03003E68[];
extern u16 func_08147830(u16 color, u16 reference, u8 amount, u8 mode);
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* Complete [0x08147E28, 0x08147EC8): 160 bytes, 73 instructions. */
PaletteTransition *func_08147E28(u16 start, u16 count, u16 duration,
                                const u16 *source, u16 reference,
                                u8 amount, u8 mode)
{
    u16 end = start + count - 1;
    u16 index;
    u16 source_index;

    if (end > 511)
        end = 511;

    for (index = start, source_index = 0; index <= end; index++, source_index++)
        data_03003E68[index].color = func_08147830(source[source_index],
                                                 reference, amount, mode);

    return func_08146E54(start, end, duration, 0);
}
