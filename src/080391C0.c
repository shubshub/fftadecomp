#include "ffta.h"

extern u16 *func_0808B8E4(void *window, u32 layer, u32 x, u32 y);

/* Complete target: [0x080391C0, 0x0803920C), 76 bytes. */
void func_080391C0(void *window, u16 tile)
{
    u16 *map;
    s32 row;
    s32 column;

    tile += 0xc000;
    map = func_0808B8E4(window, 1, 2, 2);
    for (row = 0; row < 7; row++) {
        for (column = 0; column < 14; column++) {
            map[column] = tile++;
            map[column + 27] = tile++;
        }
        map += 54;
    }
}
