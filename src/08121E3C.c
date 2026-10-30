#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u8 field_0E;
} State08121E3C;

extern State08121E3C *data_020159CC;

/* Complete [0x08121E3C, 0x08121E48), 12 bytes.
 * 01 48 00 68 80 7B 70 47 CC 59 01 02
 */
u8 func_08121E3C(void)
{
    return data_020159CC->field_0E;
}
