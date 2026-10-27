#include "ffta.h"

typedef struct PaletteState080137C0 {
    u8 unknown_00[0xA];
    u8 mode;
} PaletteState080137C0;

extern u16 func_08013794(u8 selection);
extern u16 data_03003860[];
extern u16 data_0500018C;

/* Complete [0x080137C0, 0x080137FE): 62 bytes, 25 instructions. */
void func_080137C0(PaletteState080137C0 *state, u8 selection)
{
    if (selection) {
        state->mode = 3;
        if (selection <= 4) {
            u16 color = func_08013794(selection);
            data_03003860[0xC6] = color;
            data_0500018C = color;
        }
    } else {
        state->mode = 0;
    }
}
