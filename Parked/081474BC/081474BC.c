#include "ffta.h"

typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteRecord;

extern PaletteRecord data_03003E68[];
extern u16 func_08148384(u16 color, u16 first, u16 second, u16 third);
extern void func_08146E54(u16 start, u16 end, u16 mode, u32 flags);

/* Complete target: [0x081474BC, 0x081475A4), 232 bytes, 109 instructions. */
void func_081474BC(u16 start, u16 count, u16 mode, const u16 *colors,
                   u16 first, u16 second, u16 third)
{
    u16 end = start + count - 1;
    u16 index;
    u16 sourceIndex;

    if (end > 0x1FF)
        end = 0x1FF;
    for (index = start, sourceIndex = 0; index <= end; index++, sourceIndex++)
    {
        u16 color;
        u16 red;
        u16 green;
        u16 blue;

        color = colors[sourceIndex];
        red = color & 0x1F;
        green = color & 0x3E0;
        green >>= 5;
        blue = color & 0x7C00;
        blue >>= 10;

        red = red < 3 ? 3 : red;
        green = green < 3 ? 3 : green;
        blue = blue < 3 ? 3 : blue;
        data_03003E68[index].color = func_08148384(red | (green << 5) | (blue << 10),
                                                first, second, third);
    }
    func_08146E54(start, end, mode, 0);
}
