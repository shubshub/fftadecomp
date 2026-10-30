#include "ffta.h"

typedef struct {
    u8 unknown_00[0x8D4];
    u32 field_8D4;
} State08121E08;

extern State08121E08 *data_020159CC;

/* Complete [0x08121E08, 0x08121E1C): 20 bytes, 6 reachable Thumb instructions.
 * 02490968024a891808607047cc590102d4080000
 */
void func_08121E08(u32 value)
{
    data_020159CC->field_8D4 = value;
}
