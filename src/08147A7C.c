#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteEntry08147A7C;

typedef struct PaletteTransition PaletteTransition;

extern PaletteEntry08147A7C data_03003E68[];
extern PaletteTransition *func_08146E54(u16 start, u16 end, u16 duration, u16 mode);

/* Target: complete [0x08147A7C, 0x08147AD0), 84 bytes.
 * 70b50004040c0904090c1204160c611801390904090c0d48814200d9011c231c
 * 8c420bd80a4d00225800c018800040190280581c0004030c8b42f5d9201c321c
 * 0023fff7c9f970bc02bc0847ff010000683e0003
 */
PaletteTransition *func_08147A7C(u16 start, u16 count, u16 duration)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 511)
        end = 511;

    for (index = start; index <= end; index++)
        data_03003E68[index].color = 0;

    return func_08146E54(start, end, duration, 0);
}
