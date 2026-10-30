#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry08147D2C;

typedef struct PaletteTransition PaletteTransition;

extern PaletteEntry08147D2C data_03003E68[];
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* Target: complete [0x08147D2C, 0x08147D94), 104 bytes.
 * f0b51f1c0004050c0904090c1204120c94466918013909040b0c1148834200d9031c
 * 2a1c00249d4210d80e4e51008918890089196000c01900880880501c0004020c601c
 * 0004040c9a42efd9281c191c62460023fff768f8f0bc02bc08470000ff010000683e0003
 */
PaletteTransition *func_08147D2C(u16 start, u16 count, u16 duration,
                                const u16 *source)
{
    u16 end = start + count - 1;
    u16 index;
    u16 source_index;

    if (end > 511)
        end = 511;

    for (index = start, source_index = 0; index <= end; index++, source_index++)
        data_03003E68[index].color = source[source_index];

    return func_08146E54(start, end, duration, 0);
}
