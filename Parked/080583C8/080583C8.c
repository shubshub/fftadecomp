#include "ffta.h"

/* 0x080583C8..0x080583FA: 50 bytes. */
typedef struct {
    u8 unknown_00[0x18];
    s16 count;
    s16 position;
} MenuWindow;

int func_080583C8(const MenuWindow *window, u16 direction)
{
    switch (direction) {
    case 0x40:
        if (window->position == 0)
            return 0;
        break;
    case 0x80:
        if (window->position + 3 >= window->count)
            return 0;
        break;
    default:
        return 0;
    }
    return 1;
}
