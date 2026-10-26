#include "ffta.h"

struct State08121DA8 {
    u8 unknown_00[0x898];
    u32 field_898;
};

extern struct State08121DA8 *data_020159CC;

/* Target: [0x08121DA8, 0x08121DBC), 20 bytes.
 * 02490968024a891808607047cc59010298080000
 */
void func_08121DA8(u32 value)
{
    data_020159CC->field_898 = value;
}
