#include "ffta.h"

/* Complete [0x0814731C, 0x081473E4): 200 bytes, 92 instructions. */
typedef struct {
    u16 color;
    u8 unknown_02[10];
} PaletteRecord0814731C;

extern u16 data_03003860[];
extern PaletteRecord0814731C data_03003E68[];
extern u16 func_08148384(u16, u16, u16, u16);
extern u32 func_08146E54(u16, u16, u16, u32);

u32 func_0814731C(u16 start, u16 count, u16 mode, u16 amount)
{
    u16 end = start + count - 1;
    u16 index;

    if (end > 0x1FF)
        end = 0x1FF;
    for (index = start; index <= end; index++) {
        u16 color = data_03003860[index];
        u16 red = color & 0x1F;
        u16 green = 0x3E0 & color;
        u16 blue;

        green >>= 5;
        blue = color & 0x7C00;
        blue >>= 10;

        red = red < 3 ? 3 : red;
        green = green < 3 ? 3 : green;
        blue = blue < 3 ? 3 : blue;
        data_03003860[index] = red | (green << 5) | (blue << 10);
        data_03003E68[index].color = func_08148384(data_03003860[index],
                                                 amount, amount, amount);
    }
    return func_08146E54(start, end, mode, 0);
}
