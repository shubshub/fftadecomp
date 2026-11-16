#include "ffta.h"

extern u16 data_03003860[];
extern u8 func_080DBC08(const void *object);
extern u8 func_080DBC18(void *object, u8 palette);
extern u16 func_081477DC(u16 color);

/* Target: [0x0811CC9C, 0x0811CD4C), 176 bytes, 83 instructions. */
void func_0811CC9C(void **objects, u8 *saved_palettes, u8 count)
{
    u8 palette;
    u8 j;

    for (j = 0; j < count; j++) {
        palette = func_080DBC08(objects[j]);
        if (palette > 3)
            palette = 3;
        saved_palettes[j] = func_080DBC18(objects[j], palette + 6);
    }

    for (palette = 0; palette < 4; palette++) {
        for (j = 0; j < 16; j++) {
            u16 color;

            if (palette < 3)
                color = data_03003860[0x100 + palette * 16 + j];
            else
                color = data_03003860[0x1F0 + j];
            data_03003860[0x100 + (palette + 6) * 16 + j] = func_081477DC(color);
        }
    }
}
