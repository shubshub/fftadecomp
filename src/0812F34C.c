#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u32 field_08;
} State0812F34C;

extern State0812F34C data_0200F3F0;

/* Complete [0x0812F34C, 0x0812F358): 12 bytes, 3 instructions.
 * 0149886070470000f0f30002
 */
void func_0812F34C(u32 value)
{
    data_0200F3F0.field_08 = value;
}
