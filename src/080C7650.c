/* Target bytes (24):
 * 00 b5 04 48 01 21 ff f7 0f fd 00 06 00 0e 02 bc
 * 08 47 00 00 b0 58 01 02
 */
#include "ffta.h"

struct Object080C7078;

extern struct Object080C7078 data_020158B0;
extern u32 func_080C7078(struct Object080C7078 *object, u8 value);

u8 func_080C7650(void)
{
    return func_080C7078(&data_020158B0, 1);
}
