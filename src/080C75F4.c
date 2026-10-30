/* Target bytes (28):
 * 00 b5 04 48 04 49 3c f7 8f fa 00 06 00 0e 02 bc
 * 08 47 00 00 60 9a 14 08 68 9a 14 08
 */
#include "ffta.h"

extern const char data_08149A60[];
extern const char data_08149A68[];
extern s32 func_08003B1C(const char *first, const char *second);

u8 func_080C75F4(void)
{
    return (u8)func_08003B1C(data_08149A60, data_08149A68);
}
