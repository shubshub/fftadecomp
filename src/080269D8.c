#include "ffta.h"

/* Target 0x080269D8..0x08026A30, 88 bytes:
 * f0b5051c0027002600246000291c2a3109180888002808d0a4f000fc0006002804d0701c0006060e00e001270134042cebdd002f0cd0281ca6f07cfd0006000e082801d1012e01d0002e01d1012000e00020f0bc02bc0847
 */
typedef struct {
    u8 unknown_00[0x2A];
    u16 equipment[5];
} Unit080269D8;

extern u8 func_080CB1F4(u16 item);
extern u8 func_080CD50C(const Unit080269D8 *unit);

u8 func_080269D8(const Unit080269D8 *unit)
{
    u8 empty = 0;
    u8 count = 0;
    s32 index;

    for (index = 0; index < 5; index++) {
        if (unit->equipment[index] != 0) {
            if (func_080CB1F4(unit->equipment[index]))
                count++;
        } else {
            empty = 1;
        }
    }
    if (empty) {
        u8 kind = func_080CD50C(unit);

        if ((kind == 8 && count == 1) || count == 0)
            return 1;
    }
    return 0;
}
