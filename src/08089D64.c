/* Target bytes (20):
 * 03 4a 81 18 09 78 c9 00 40 18 00 79 70 47 00 00
 * 05 01 00 00
 */
#include "ffta.h"

u8 func_08089D64(u8 *object)
{
    object += object[0x105] * 8;
    return object[4];
}
