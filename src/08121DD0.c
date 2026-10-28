#include "ffta.h"

/* Target: complete [0x08121DD0, 0x08121DE4), 20 bytes including literals. */
typedef struct {
    u8 unknown_00[0x89c];
    u32 field_89c;
} State08121DD0;

extern State08121DD0 *data_020159CC;

void func_08121DD0(u32 value)
{
    data_020159CC->field_89c = value;
}
