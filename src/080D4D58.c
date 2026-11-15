#include "ffta.h"

/* Target: 0x080D4D58..0x080D4DA0, 72 bytes including the literal pool.
 * 70b584b00006030e09066a46064870c870c200681060002908d098006844026810884021
 * 084307e0b49a1408980068440268118803480840108004b070bc01bc00470000bfff0000
 */
typedef struct {
    u16 *control[4];
} BackgroundControls;

/* The BG0CNT..BG3CNT shadows at 0x03000942..0x03000948. */
extern const BackgroundControls data_08149AB4;

void func_080D4D58(u8 background, u8 mosaic)
{
    BackgroundControls controls = data_08149AB4;

    if (mosaic)
        *controls.control[background] |= 0x40;
    else
        *controls.control[background] &= ~0x40;
}
