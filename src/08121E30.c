#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u8 field_0E;
} State08121E30;

extern State08121E30 *data_020159CC;

/* Complete [0x08121E30, 0x08121E3C): 12 bytes, 4 instructions.
 * 0149096888737047cc590102
 */
void func_08121E30(u8 value)
{
    data_020159CC->field_0E = value;
}
