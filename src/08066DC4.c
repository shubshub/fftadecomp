#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 mode;
} Menu;

extern u8 func_080099A4(u8 mode);

/* Complete target: [0x08066DC4, 0x08066DDC), 24 bytes, 11 instructions. */
u32 func_08066DC4(Menu *menu)
{
    if (func_080099A4(menu->mode) != 0)
        return 1;
    return 0;
}
