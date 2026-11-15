#include "ffta.h"

extern u16 func_08141860(s16 horizontal, s16 vertical);
extern const void *const data_083943BC[];

/* Complete [0x080A83EC, 0x080A8430): 68 bytes, 30 instructions.
 * 00b512041214000400141b041b1409040914121a120412145b1a1b041b14101c191c99f0
 * 27fa0004000e0830ff2108400009034980004018006802bc08470000bc433908
 *
 * The same computation is inline in func_080A0FF0, where the four operands
 * are loaded in this order before either subtraction.
 */
const void *func_080A83EC(s16 from_x, s16 from_z, s16 to_x, s16 to_z)
{
    s32 end_x;
    s32 start_x;
    s32 end_z;
    s32 start_z;
    u32 direction;

    end_x = to_x;
    start_x = from_x;
    end_z = to_z;
    start_z = from_z;
    direction = func_08141860(end_x - start_x, end_z - start_z) >> 8;
    direction = ((direction + 8) & 0xFF) >> 4;
    return data_083943BC[direction];
}
