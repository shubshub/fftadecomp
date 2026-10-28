#include "ffta.h"

extern u16 data_03003860[];
extern u8 func_080DBC08(void *object);
extern u8 func_080DBC18(void *object, u8 palette);
extern u16 func_081477DC(u16 color);

/* Target: [0x0811CC9C, 0x0811CD4C), 176 bytes, 83 instructions. */
void func_0811CC9C(void **objects, u8 *saved_palettes, u8 count)
{
    u8 i;
    u8 j;
    u16 *palette_buffer = data_03003860;

    for (j = 0; j < count; j++) {
        i = func_080DBC08(objects[j]);
        if (i > 3)
            i = 3;
        saved_palettes[j] = func_080DBC18(objects[j], i + 6);
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            u16 color;

            if (i < 3)
                color = palette_buffer[j + 0x100 + i * 16];
            else
                color = palette_buffer[j + 0x1f0];
            palette_buffer[j + 0x100 + (i + 6) * 16] = func_081477DC(color);
        }
    }
}
