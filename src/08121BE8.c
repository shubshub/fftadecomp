/* Target bytes (12):
 * 01 48 00 68 40 6d 70 47 cc 59 01 02
 */
#include "ffta.h"

struct ObjectWordAt54 {
    u32 unknown_00[0x15];
    u32 value_54;
};

extern struct ObjectWordAt54 *data_020159CC;

u32 func_08121BE8(void)
{
    return data_020159CC->value_54;
}
