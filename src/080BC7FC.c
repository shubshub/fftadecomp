/* Target bytes (20):
 * 00 b5 03 48 fe f7 72 fb 00 06 00 0e 02 bc 08 47
 * c8 00 01 02
 */
#include "ffta.h"

struct Object080BAEE8;

extern struct Object080BAEE8 data_020100C8;
extern u32 func_080BAEE8(struct Object080BAEE8 *object);

u8 func_080BC7FC(void)
{
    return func_080BAEE8(&data_020100C8);
}
